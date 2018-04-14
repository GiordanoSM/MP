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
	int error;
	TreeNode* old_location = *current_location;
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
		return 1;

	return error;
}


} // namespace tree