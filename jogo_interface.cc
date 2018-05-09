#define ASSERT_DEBUG
#include "../include/jogo_interface.h"

#include <stdlib.h>
#include <assert.h>
#include <iostream>

namespace tree {

/** \brief Tree builder interface

		The function takes one argument returning an integer value.\n
		It gives the user the option of loading a tree (game) using LoadTree() or creating a Default using GenericTree().
		\param t a Tree type pointer.
		\return The state of the operation, 0 if it was successful, -1 if the command wasn't valid and another one if it wasn't successful.
		\pre "t" must have been previously alocated. 
		\sa LoadTree() GenericTree() CreateTree()
*/

int StartTree (Tree *t)
{
	//Assertiva de entrada
	#ifdef ASSERT_DEBUG
		assert( t != NULL ) ; // retirado se ASSERT_DEBUG não definido
	#endif

	unsigned int error = 0;
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
	{
		std::cout << "\n **** Por favor, de uma das respostas esperadas. \n\n";
		return -1;
	}

	return error;
} // StartTree

/** \brief Answer interpreter interface

		The function takes two arguments returning an integer value.\n
		It interpretates the user's possible answer. \n If it's a question: (Sim) go to the right node, (Nao) go to the left node, (Opcoes) open the question options menu;
		if it's a guess: (Sim) game ends, (Nao) ask for the answer and a new question, (Opcoes) open the answer options menu.
		\param current_location a TreeNode type pointer of pointer that indicates what node the game is processing.
		\param answer a string that indicates the answer given by the user.
		\return The state of the operation, 0 if it was successful, -1 if the command wasn't valid or the same tree node needs to
		be processed again, -2 if the game ended with the user winning and another one if it wasn't successful.
		\pre "current_location" must have been previously alocated.
		\sa OptionsQuestion() OptionsAnswer() AddRightNode() AddLeftNode() ChangeNodeData()
*/

int AnswerInterpreter (TreeNode **current_location, std::string answer)
{
	const unsigned int leaf = 1;
	const unsigned int not_leaf = 0;
	//Assertiva de entrada
	#ifdef ASSERT_DEBUG
		assert( current_location != NULL ) ;
		assert( (*current_location) != NULL ) ; // retirado se ASSERT_DEBUG não definido
	#endif

	//Assertiva de estrutura
	#ifdef ASSERT_DEBUG // retirado se ASSERT_DEBUG não definido
		if ((*current_location)->defining_element == not_leaf)
		{
			assert( (*current_location)->right_node != NULL ) ;
			assert( (*current_location)->left_node != NULL ) ;
		}
		else 
		{
			assert( (*current_location)->right_node == NULL ) ;
			assert( (*current_location)->left_node == NULL ) ;
		}
	#endif	

	int error = 0;
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
				std::cout << "\n$$$$$ Qual seria a sua resposta a essa pergunta? (Sim/Nao) $$$$$\n\n";
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

/** \brief Change question interface

		The function takes one argument.\n
		It rewrites a existent question using the function ChangeNodeData().
		\param current_location a TreeNode type pointer.
		\return void.
		\pre "current_location" must have been previously alocated and must be a "question".
		\sa ChangeNodeData()
*/

void RewriteQuestion (TreeNode* current_location)
{
	//Assertiva de entrada
	#ifdef ASSERT_DEBUG
		assert( current_location != NULL ) ; // retirado se ASSERT_DEBUG não definido
	#endif

	unsigned int repeter = 1;
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

/** \brief Delete question interface

		The function takes one argument returning an integer value.\n
		It rewrites a existent question in to a answer and deletes all the underlying nodes using the function DeleteSubtree().
		\param current_location a TreeNode type pointer.
		\return The state of the operation, 0 if it was successful, -1 if the operation isn't allowed and 
		the node needs to be processed again ,and another one if it wasn't successful.
		\pre "current_location" must have been previously alocated and must be a "question".
		\sa ChangeNodeData() DeleteSubtree()
*/

int DeleteQuestion (TreeNode* current_location)
{
	//Assertiva de entrada
	#ifdef ASSERT_DEBUG
		assert( current_location != NULL ) ; // retirado se ASSERT_DEBUG não definido
	#endif

	int error = 0;
	const unsigned int leaf = 1;
	unsigned int repeter = 1;

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

/** \brief Rewrite answer interface

		The function takes one argument.\n
		It rewrites a existent guess using the function ChangeNodeData().
		\param current_location a TreeNode type pointer.
		\return void.
		\pre "current_location" must have been previously alocated and must be a "answer".
		\sa ChangeNodeData() DeleteSubtree()
*/

void RewriteAnswer (TreeNode* current_location)
{
	//Assertiva de entrada
	#ifdef ASSERT_DEBUG
		assert( current_location != NULL ) ; // retirado se ASSERT_DEBUG não definido
	#endif

	unsigned int repeter = 1;
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

/** \brief Question options menu

		The function takes one argument returning an integer value.\n
		It gives the user the possibility to delete or rewrite the question ,or to simply resume the game.
		\param current_location a TreeNode type pointer.
		\return The state of the operation, 0 if it was successful, -1 if the node needs to be processed again (resume) and another one if it wasn't successful.
		\pre "current_location" must have been previously alocated and must be a "question".
		\sa DeleteQuestion() RewriteQuestion()
*/

int OptionsQuestion (TreeNode* current_location)
{
	//Assertiva de entrada
	#ifdef ASSERT_DEBUG
		assert( current_location != NULL ) ; // retirado se ASSERT_DEBUG não definido
	#endif

	int error = 0;
	std::string answer;
	unsigned int repeter = 1;

	while (repeter)
	{

		std::cout << "\n*******************************\n";
		std::cout << " Deletar a pergunta: (Deletar)\n";
		std::cout << " Modificar a pergunta: (Escrever)\n";
		std::cout << " Retomar o jogo: (Voltar)\n";
		std::cout << "*********************************\n\n";

		std::cin >> answer;

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

/** \brief Answer options menu

		The function takes one argument returning an integer value.\n
		It gives the user the possibility to rewrite the guess or to simply resume the game.
		\param current_location a TreeNode type pointer.
		\return The state of the operation, 0 if it was successful, -1 if the node needs to be processed again (resume) and another one if it wasn't successful.
		\pre "current_location" must have been previously alocated and must be a "answer".
		\sa RewriteAnswer()
*/

int OptionsAnswer (TreeNode* current_location)
{
	//Assertiva de entrada
	#ifdef ASSERT_DEBUG
		assert( current_location != NULL ) ; // retirado se ASSERT_DEBUG não definido
	#endif

	int error = 0;
	std::string answer;
	unsigned int repeter = 1;

	while (repeter)
	{
		std::cout << "\n*******************************\n";
		std::cout << " Modificar a resposta: (Escrever)\n";
		std::cout << " Retomar o jogo: (Voltar)\n";
		std::cout << "*********************************\n\n";

		std::cin >> answer;


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

/** \brief Saving interface

		The function takes one argument returning an integer value.\n
		It gives the user the possibility to save the used and possibly modified tree (game) in a text file using the function SaveTree().
		\param t a Tree type pointer.
		\return The state of the operation, 0 if it was successful and another one if it wasn't.
		\pre "t" must have been previously alocated. 
		\sa SaveTree()
*/

int SavingInterface (Tree* t)
{
	//Assertiva de entrada
	#ifdef ASSERT_DEBUG
		assert( t != NULL ) ; // retirado se ASSERT_DEBUG não definido
	#endif

	unsigned int repeter = 1;
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
			unsigned int repeter_2 = 1;

			while (repeter_2)
			{
				std::cout << "\n **** Voce tem certeza que nao quer salvar o jogo? (Sim/Nao) \n"; 
				std::cout << "### Lembre-se que todas as perguntas e adivinhacoes serao perdidas.\n\n";		
				std::cin >> answer;
				getchar();

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