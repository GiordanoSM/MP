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
	std:string new_element;
	std:string new_question;
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
		else 
		{
			cout << "\n **** Por favor, dê uma resposta do tipo Sim ou Nao.\n\n";
			return -1;
		}

	} // not_leaf

	else 
	{ 
		if ( answer == "Sim" || answer == "sim" || answer == "SIM" )
		{
			cout << "\n$$$$$ Haha! Eu ganhei denovo. $$$$$\n\n";
		} // Sim

		else if ( answer == "Nao" || answer == "nao" || answer == "NAO" )
		{
			cout << "\n$$$$$ Ah... Que pena. Qual era a resposta correta? $$$$$\n\n";
			cin >> new_element;
			getchar();

			cout << "\n$$$$$ Digite a pergunta que voce a faria para diferenciar minha resposta da sua. $$$$$\n\n";
			cin >> new_question;
			getchar();

			while ((*current_location)->defining_element == leaf)
			{
				cout << "\n$$$$$ Qual seria a sua resposta a essas pergunta? (Sim/Nao) $$$$$\n\n";
				cin << answer;
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
					cout << "\n **** Por favor, dê uma resposta do tipo Sim ou Nao.\n\n";
				}

			} // while

		} // Nao

		else 
		{
			cout << "\n **** Por favor, dê uma resposta do tipo Sim ou Nao.\n\n";
			return -1;
		}	
	} // else


	return error;
} // AnswerInterpreter


} // namespace tree