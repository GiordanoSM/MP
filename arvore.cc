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
		n->right_node->father_node = n;
		return 0;
	}

	else 
		return 1;
} // AddRightNode

int AddLeftNode (TreeNode* n)
{
	if(n->left_node == NULL)
	{
		n->left_node = new (std::nothrow) TreeNode();
		n->left_node->father_node = n;
		return 0;
	}

	else 
		return 1;
} // AddLeftNode

int DeleteNode (TreeNode** n)
{
	if((*n)->left_node == NULL && (*n)->right_node == NULL)
	{
		delete *n;
		*n = NULL;
		return 0;
	}

	else 
	{
		return 1;
	}
} // DeleteNode

int DeleteSubtree (TreeNode** n)
{
	int error = 0;

	if ((*n)->father_node != NULL) // Caso n for a raiz da árvore
	{
		if ((*n)->left_node != NULL)
		{
			error += DeleteSubtree (&((*n)->left_node));
		}

		if ((*n)->right_node != NULL)
		{
			error += DeleteSubtree (&((*n)->right_node));
		}

		error += DeleteNode (n);
	} // father_node

	else 
		error = -1;
	
	return error;
} //DeleteSubtree

} // namespace tree