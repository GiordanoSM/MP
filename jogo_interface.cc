#include "../include/jogo_interface.h"

#include <stdlib.h>
#include <iostream>

namespace tree {

int StartTree (Tree *t)
{
	int error = 0;
	std::string option;
	std::string file_name;

	std::cout << "****************# Qual arvore devera ser utilizada? (Arquivo/Default) #****************\n\n";

	std::cin >> option;
	getchar();

	if (option.compare ("Arquivo") == 0 || option.compare ("ARQUIVO") == 0 || option.compare ("arquivo") == 0)
	{
		CreateTree(t);
		std::cout << "\n****************# Informe o nome e extensao do arquivo. #****************\n";
		std::cout << "## Obs: Caso ele nao esteja no mesmo diretorio que esse jogo, informe seu caminho.\n\n";

		std::cin >> file_name;
		getchar();
		error = LoadTree (t, file_name);

		if (error != 0)
		{
			std::cout << "\n ERROR: Arquivo nao existente\n";
			std::cout << "## Obs: Se o problema persistir existe um problema com o carregamento do arquivo\n\n";
		}
	}

	else if (option.compare ("Default") == 0 || option.compare ("default") == 0 || option.compare ("DEFAULT") == 0)
	{
		error = GenericTree (t);
	}


	else
		return -1;

	return error;
} // StartTree


int AnswerInterpreter (TreeNode **current_location, std::string answer)
{
	int error = 0;
	int leaf = 1;
	int not_leaf = 0;
	std::string new_element;
	std::string new_question;
	TreeNode* old_location = *current_location;

	if ((*current_location)->defining_element == not_leaf)
	{
		if ( answer == "Sim" || answer == "sim" || answer == "SIM" )
		{
			*current_location = (*current_location)->right_node;
			error = (old_location == *current_location);
		}
		else if ( answer == "Nao" || answer == "nao" || answer == "NAO" )
		{
			*current_location = (*current_location)->left_node;
			error = (old_location == *current_location);
		}
		else if ( answer == "Opcoes" || answer == "opcoes" || answer == "OPCOES" )
		{
			error = OptionsQuestion (*current_location);
		}
		else 
		{
			std::cout << "\n **** Por favor, de uma resposta do tipo Sim ou Nao.\n\n";
			return -1;
		}

	} // not_leaf

	else 
	{ 
		if ( answer == "Sim" || answer == "sim" || answer == "SIM" )
		{
			std::cout << "\n$$$$$ Haha! Eu ganhei denovo. $$$$$\n\n";
		} // Sim

		else if ( answer == "Opcoes" || answer == "opcoes" || answer == "OPCOES" )
		{
			error = OptionsAnswer (*current_location);
		}

		else if ( answer == "Nao" || answer == "nao" || answer == "NAO" )
		{
			std::cout << "\n$$$$$ Ah... Que pena. Qual era a resposta correta? $$$$$\n\n";
			std::getline (std::cin, new_element);

			std::cout << "\n$$$$$ Digite a pergunta que voce a faria para diferenciar minha resposta da sua. $$$$$\n\n";
			std::getline (std::cin, new_question);

			while ((*current_location)->defining_element == leaf)
			{
				std::cout << "\n$$$$$ Qual seria a sua resposta a essas pergunta? (Sim/Nao) $$$$$\n\n";
				std::cin >> answer;
				getchar();

				if ( answer == "Sim" || answer == "sim" || answer == "SIM" )
				{
					error += AddRightNode (*current_location);
					ChangeNodeData ((*current_location)->right_node, new_element);

					error += AddLeftNode (*current_location);
					ChangeNodeData ((*current_location)->left_node, (*current_location)->message);

					ChangeNodeData (*current_location, new_question);
				}

				else if ( answer == "Nao" || answer == "nao" || answer == "NAO" )
				{
					error += AddLeftNode (*current_location);
					ChangeNodeData ((*current_location)->left_node, new_element);

					error += AddRightNode (*current_location);
					ChangeNodeData ((*current_location)->right_node, (*current_location)->message);

					ChangeNodeData (*current_location, new_question);
				}

				else 
				{
					std::cout << "\n **** Por favor, de uma resposta do tipo Sim ou Nao.\n\n";
				}

			} // while

			return -2;
		} // Nao

		else 
		{
			std::cout << "\n **** Por favor, de uma resposta do tipo Sim ou Nao.\n\n";
			return -1;
		}	
	} // else


	return error;
} // AnswerInterpreter

void RewriteQuestion (TreeNode* current_location)
{
	int repeter = 1;
	std::string answer;
	while (repeter)
	{
		std::cout << "\n **** Voce tem certeza que quer reescrever a pergunta? (Sim/Nao) \n"; 
		std::cout << "### Lembre-se que as proximas perguntas e adivinhacoes podem nao ser compativeis.\n\n";
		std::cin >> answer;
		getchar();
	
		if ( answer == "Sim" || answer == "sim" || answer == "SIM" )
		{
			std::cout << "\n *** Nova pergunta: ";
			std::getline(std::cin, answer);

			ChangeNodeData (current_location, answer);

			repeter = 0;
		}
		else if ( answer == "Nao" || answer == "nao" || answer == "NAO" )
		{
			repeter = 0;
		}
		else 
		{
			std::cout << "\n **** Por favor, de uma resposta do tipo Sim ou Nao.\n\n";
		}
	}	// repeter

} // RewriteQuestion

int DeleteQuestion (TreeNode* current_location)
{
	int error = 0;
	int leaf = 1;
	int repeter = 1;

	std::string answer;

	if (current_location->father_node != NULL) // Se não for a raiz
	{
		while (repeter)
		{
			std::cout << "\n **** Voce tem certeza que quer apagar a pergunta? (Sim/Nao) \n"; 
			std::cout << "### Lembre-se que as proximas perguntas e adivinhacoes serao perdidas.\n\n";
			std::cin >> answer;
			getchar();
		
			if ( answer == "Sim" || answer == "sim" || answer == "SIM" )
			{
				error += DeleteSubtree (&current_location->right_node);
				error += DeleteSubtree (&current_location->left_node);
				current_location->defining_element = leaf;

				std::cout << "\n **** Escreva uma possivel nova resposta para ficar no lugar da antiga pergunta **** \n\n";
				std::getline(std::cin, answer);

				ChangeNodeData (current_location, answer);

				repeter = 0;
			}
			else if ( answer == "Nao" || answer == "nao" || answer == "NAO" )
			{
				repeter = 0;
			}
			else 
			{
				std::cout << "\n **** Por favor, de uma resposta do tipo Sim ou Nao.\n\n";
			}
		}	// repeter
	} // if

	else 
	{
		std:: cout << "\n ### Nao e permitido apagar a arvore inteira.\n";
		return -1;
	} 

	return error;
} // DeleteQuestion

void RewriteAnswer (TreeNode* current_location)
{
	int repeter = 1;
	std::string answer;
	while (repeter)
	{
		std::cout << "\n **** Voce tem certeza que quer reescrever a resposta? (Sim/Nao) \n\n"; 
		std::cin >> answer;
		getchar();
	
		if ( answer == "Sim" || answer == "sim" || answer == "SIM" )
		{
			std::cout << "\n *** Nova resposta: ";
			std::getline(std::cin, answer);

			ChangeNodeData (current_location, answer);

			repeter = 0;
		}
		else if ( answer == "Nao" || answer == "nao" || answer == "NAO" )
		{
			repeter = 0;
		}
		else 
		{
			std::cout << "\n **** Por favor, de uma resposta do tipo Sim ou Nao.\n\n";
		}
	}	// repeter

} // RewriteAnswer

int OptionsQuestion (TreeNode* current_location)
{
	int error = 0;
	std::string answer;
	int repeter = 1;

	std::cout << "\n*******************************\n";
	std::cout << " Deletar a pergunta: (Deletar)\n";
	std::cout << " Modificar a pergunta: (Escrever)\n";
	std::cout << " Retomar o jogo: (Voltar)\n";
	std::cout << "*********************************\n\n";

	std::cin >> answer;

	while (repeter)
	{

		if ( answer == "Deletar" || answer == "deletar" || answer == "DELETAR" )
		{
			repeter = 0;
			error = DeleteQuestion (current_location);
		}

		else if ( answer == "Escrever" || answer == "escrever" || answer == "ESCREVER" )
		{
			repeter = 0;
			RewriteQuestion (current_location);
		}

		else if ( answer == "Voltar" || answer == "voltar" || answer == "VOLTAR" )
		{
			repeter = 0;
			error = -1;
		}

		else	
		{
			std::cout << "\n **** Por favor, de uma das respostas esperadas.\n\n";
		}
	}	// while

	return error;
} // OptionsQuestion

int OptionsAnswer (TreeNode* current_location)
{
	int error = 0;
	std::string answer;
	int repeter = 1;

	std::cout << "\n*******************************\n";
	std::cout << " Modificar a resposta: (Escrever)\n";
	std::cout << " Retomar o jogo: (Voltar)\n";
	std::cout << "*********************************\n\n";

	std::cin >> answer;

	while (repeter)
	{
		if ( answer == "Escrever" || answer == "escrever" || answer == "ESCREVER" )
		{
			repeter = 0;
			RewriteAnswer (current_location);
		}

		else if ( answer == "Voltar" || answer == "voltar" || answer == "VOLTAR" )
		{
			repeter = 0;
			error = -1;
		}

		else	
		{
			std::cout << "\n **** Por favor, de uma das respostas esperadas. \n\n";
		}
	}	// while

	return error;
} // OptionsAnswer

int SavingInterface (Tree* t)
{
	int repeter = 1;
	int error = 0;
	std::string file_name, answer;
	while (repeter)
	{
		std::cout << "\n>>>>>> Deseja salvar o jogo atual para usa-lo no futuro? (Sim/Nao)\n\n";
		std::cin >> answer;
		getchar();

		if ( answer == "Sim" || answer == "sim" || answer == "SIM" )
		{
			std::cout << "\n*******# Informe o nome e extensao do arquivo em que o jogo sera salvo. (.txt) #*******\n";
			std::cout << "## Obs: Caso ele nao esteja no mesmo diretorio que esse jogo, informe seu caminho.\n\n";
			std::cin >> file_name;
			getchar();

			error = SaveTree (t, file_name);

			repeter = 0;
		}

		else if ( answer == "Nao" || answer == "nao" || answer == "NAO" )
		{
			int repeter_2 = 1;

			std::cout << "\n **** Voce tem certeza que nao quer salvar o jogo? (Sim/Nao) \n"; 
			std::cout << "### Lembre-se que todas as perguntas e adivinhacoes serao perdidas.\n\n";		
			std::cin >> answer;
			getchar();

			while (repeter_2)
			{
				if ( answer == "Sim" || answer == "sim" || answer == "SIM" )
				{
					repeter_2 = 0;
					repeter = 0;
				}

				else if ( answer == "Nao" || answer == "nao" || answer == "NAO" )
				{
					repeter_2 = 0;
					repeter = 1;
				}

				else
				{
					std::cout << "\n **** Por favor, de uma resposta do tipo Sim ou Nao.\n\n";
				}
			} // repeter_2
			
		}

		else 
		{
			std::cout << "\n **** Por favor, de uma resposta do tipo Sim ou Nao.\n\n";
		}
	}	// repeter

	return error;
} // SavingInterface

} // namespace tree