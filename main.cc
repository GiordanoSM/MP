#include <stdlib.h>
#include <iostream>
#include <string>

#include "../include/jogo_interface.h"
#include "../include/arvore.h"

/*! \mainpage MP Project Documentation
	
	\author Giordano Suffert Monteiro
	\version 1.0
	\date 04/2018
  
  \section intro_sec Introduction
  
  This project is focused in developing the game of questions required using a binary tree focusing in a development test oriented. \n
  To use the program it's necessary the executable file of the game.
 
  \section make_sec Executing makefile
 
  The makefile related to this program must be executed in src directory and can be use with the comand: \n\n

  make test  (Will create the executable test file related to the development of the program) \n
  make maingame (Will create the game executable)

  \section doxy_sec Executing doxygen again

  If you want to generate another documentation of these files, please change the file's directories in the doxygen configuration file "configDoxy" (INPUT) to the current ones.

*/

int main ()
{	
	int error = 1;
	int jogar_novamente = 1;
	int leaf = 1;
	int not_leaf = 0;
	
	while (jogar_novamente == 1)
	{
		int repeter; // -1 quando for para repetir o mesmo loop
		std::string answer;
		tree::Tree t;
		tree::TreeNode* current_location,* old_location;

		std::cout << "---------- BEM-VINDOS AO JOGO DAS PERGUNTAS!!! -----------\n\n";
		std::cout << ">>>>>> A primeira coisa que voce deve fazer e pensar em alguma coisa, qualquer coisa.\n";
		std::cout << ">>>>>> Pronto? Agora tentarei adivinhar com base nas suas respostas ao que perguntarei sobre o que voce pensou\n\n";
		std::cout << "########## Mas primeiro voce deve escolher meu banco de dados!\n\n";

		while (error != 0)
		{
			error = tree::StartTree(&t);
		}
		
		current_location = t.root;

		std::cout << ">>>>>> Agora que estamos ambos prontos, vamos as perguntas!!!\n\n";

		while (current_location->defining_element != leaf || repeter == -1 || old_location != current_location)
		{
			old_location = current_location;
			if (current_location->defining_element == not_leaf)
			{
				std::cout << "\n>>>>>> " << current_location->message << " (Sim/Nao) (Opcoes)\n\n";
				std::cin >> answer; 
				getchar();

				repeter = tree::AnswerInterpreter (&current_location, answer);
			}

			else
			{
				std::cout << "\n>>>>>> " << "Voce pensou nisso ( " <<current_location->message << " ) ? (Sim/Nao) (Opcoes)\n\n";
				std::cin >> answer; 
				getchar();

				repeter = tree::AnswerInterpreter (&current_location, answer);
			}

			if (repeter == -2) // Se o jogo tiver errado a resposta final
				break;
			
		}

		tree::SavingInterface (&t);
		tree::DeleteTree (&t);

		std::cout << "\n>>>>>> Para jogar novamente digite (Jogar).\n";
		std::cout << "\n>>>>>> Caso contrario digite qualquer outra coisa.\n";
		std::cout << "---------- OBRIGADO POR JOGAR!!! -----------\n\n";

		std::cin >> answer;

		if (answer == "Jogar")
			jogar_novamente = 1;

		else 
			jogar_novamente = 0;
	}

	return 0;
} // main


