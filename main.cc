#include <stdlib.h>
#include <iostream>
#include <string>

#include "../include/jogo_interface.h"
#include "../include/arvore.h"

int main ()
{	
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

		tree::StartTree(&t);
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


