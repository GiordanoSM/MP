#include "../include/arvore.h"

#include <stdlib.h>
#include <iostream>

#include <bitset>

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
	int leaf = 1;
	int not_leaf = 0;
	if(n->right_node == NULL)
	{
		n->right_node = new (std::nothrow) TreeNode();
		n->right_node->father_node = n;
		n->right_node->defining_element = leaf;
		n->defining_element = not_leaf;
		return 0;
	}

	else 
		return 1;
} // AddRightNode

int AddLeftNode (TreeNode* n)
{
	int leaf = 1;
	int not_leaf = 0;
	if(n->left_node == NULL)
	{
		n->left_node = new (std::nothrow) TreeNode();
		n->left_node->father_node = n;
		n->left_node->defining_element = leaf;
		n->defining_element = not_leaf;
		return 0;
	}

	else 
		return 1;
} // AddLeftNode

int DeleteNode (TreeNode** n)
{
	int leaf = 1;
	TreeNode* father_node = (*n)->father_node;
	if((*n)->left_node == NULL && (*n)->right_node == NULL)
	{
		delete *n;
		*n = NULL;

		if (father_node != NULL && father_node->left_node == NULL && father_node->right_node == NULL)
			father_node->defining_element = leaf;

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
} // DeleteSubtree

int DeleteTree (Tree* t)
{
	int error = 0;

	if (t->root->left_node != NULL)
		error += DeleteSubtree (&(t->root->left_node));

	if (t->root->right_node != NULL)
		error += DeleteSubtree (&(t->root->right_node));

	error += DeleteNode (&(t->root));

	return error;
} // DeleteTree

void ChangeNodeData (TreeNode* n, std::string s)
{
	n->message = s;
} // Change Data

int SaveTree (Tree* t, std::string file_name)
{
	int error = 0;
	std::string my_tree;
	std::ofstream my_file;
	my_file.open (file_name, std::ios::out | std::ios::trunc);

	error += my_file.is_open();
	if (error == 0)
		return 1;

	error = 0;

	error += WriteTree (t->root, my_tree);

	my_file << my_tree;

	my_file.close();
	return error;
} // ChangeNodeData

int WriteTree (TreeNode* n, std::string my_tree)
{
	return 0;
} // WriteTree

} // namespace tree