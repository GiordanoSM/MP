#ifndef MP_SRC_JOGO_INTERFACE_H_
#define MP_SRC_JOGO_INTERFACE_H_

#include <string>
#include <fstream>

#include "../include/arvore.h"

namespace tree {

int StartTree (Tree *t);

int AnswerInterpreter (TreeNode **current_location, std::string answer);

void RewriteQuestion (TreeNode* current_location);

int DeleteQuestion (TreeNode* current_location);

void RewriteAnswer (TreeNode* current_location);

} // namespace tree

#endif