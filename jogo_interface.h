#ifndef MP_SRC_JOGO_INTERFACE_H_
#define MP_SRC_JOGO_INTERFACE_H_

#include <string>

#include "../include/arvore.h"

namespace tree {

/*StartTree
Assertivas de entrada (requisitos): "t" deve ser sido previamente alocado.

Assertivas de saida: A saida deve ser 0 se a operacao foi computada, -1 se o comando nao foi valido 
										 e um numero positivo caso nao tenha sido computada corretamente.

Interface explicita: Parametros
*/
int StartTree (Tree *t);

/*AnswerInterpreter
Assertivas de entrada (requisitos): "current_location" deve ser sido previamente alocado.

Assertivas de saida: A saida deve ser 0 se a operacao foi computada, -1 se o comando nao foi valido e 
										 o nodo precisa ser processado novamente, ou um numero positivo caso nao tenha sido computada corretamente.

Interface explicita: Parametros
*/
int AnswerInterpreter (TreeNode **current_location, std::string answer);

/*RewriteQuestion
Assertivas de entrada (requisitos): "current_location" deve ser sido previamente alocado e deve ser do tipo "pergunta".

Assertivas de saida: A saida deve ser 0 se a operacao foi computada, -1 se o comando nao foi valido, 
										 -2 se o jogo terminou com vitória do usuário e um numero positivo caso nao tenha sido computada corretamente.

Interface explicita: Parametros
*/
void RewriteQuestion (TreeNode* current_location);

/*DeleteQuestion
Contrato na especificacao: A arvore deve ser binaria.

Assertivas de entrada (requisitos): "current_location" deve ser sido previamente alocado e deve ser do tipo "pergunta".

Assertivas de saida: A saida deve ser 0 se a operacao foi computada, -1 se o comando nao foi valido e 
										 o nodo precisa ser processado novamente, ou um numero positivo caso nao tenha sido computada corretamente.

Interface explicita: Parametros
*/
int DeleteQuestion (TreeNode* current_location);

/*RewriteAnswer
Assertivas de entrada (requisitos): "current_location" deve ser sido previamente alocado e deve ser do tipo "resposta".

Assertivas de saida: Sem saida.

Interface explicita: Parametros
*/
void RewriteAnswer (TreeNode* current_location);

/*OptionsQuestion
Assertivas de entrada (requisitos): "current_location" deve ser sido previamente alocado e deve ser do tipo "pergunta".

Assertivas de saida: A saida deve ser 0 se a operacao foi computada, -1 se o nodo precisar ser 
										 processado novamente (retomar), ou um numero positivo caso nao tenha sido computada corretamente.

Interface explicita: Parametros
*/
int OptionsQuestion (TreeNode* current_location);

/*OpstionsAnswer
Assertivas de entrada (requisitos): "current_location" deve ser sido previamente alocado e deve ser do tipo "resposta".

Assertivas de saida: A saida deve ser 0 se a operacao foi computada, -1 se o nodo precisar ser 
										 processado novamente (retomar), ou um numero positivo caso nao tenha sido computada corretamente.

Interface explicita: Parametros
*/
int OptionsAnswer (TreeNode* current_location);

/*SavingInterface
Contrato na especificacao: A arvore deve ser salva em um arquivo.

Assertivas de entrada (requisitos): "t" deve ser sido previamente alocado.

Assertivas de saida: A saida deve ser 0 se a operacao foi computada e um numero positivo se nao.

Interface explicita: Parametros
*/
int SavingInterface (Tree* t);

} // namespace tree

#endif