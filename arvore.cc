#include "../include/arvore.h"

#include <stdlib.h>
#include <iostream>

namespace tree {

int CreateTree (Tree* t) 
{
	if (t->root == NULL) // Verifica se a árvore já era existente, NULL se existente
	{
		t->root = new (std::nothrow) TreeNode();
		return 0;
	}

	else 
		return 1;
} // CreateTree

int AddRightNode (TreeNode* n)
{
	if(n->right_node == NULL)
	{
		n->right_node = new (std::nothrow) TreeNode();
		return 0;
	}

	else 
		return 1;
} // AddRightNode

} // namespace tree