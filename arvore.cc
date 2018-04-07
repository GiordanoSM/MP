#include "../include/arvore.h"

#include <stdlib.h>
#include <iostream>

namespace tree {

int CreateTree (Tree* t) 
{
	if (t->root == NULL) // Verifica se a árvore já era existente, NULL se existente
	{
		t->root = new TreeNode();
		return 0;
	}

	else 
		return 1;
}

} // namespace tree