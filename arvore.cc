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

	if (my_file.is_open() == 0)
		return 1;

	error += WriteTree (t->root, &my_tree);

	my_file << my_tree;

	my_file.close();
	return error;
} // ChangeNodeData

int WriteTree (TreeNode* n, std::string* my_tree)
{
	int leaf = 1;
	int error = 0;
	std::string old_my_tree = *my_tree;
	const char divider = '|';
	const char leaf_indicator = '#';

	(*my_tree) += n->message + divider;

	if (my_tree->compare (old_my_tree) == 0)
		error += 1;

	if (n->defining_element == leaf)
		(*my_tree) += leaf_indicator;


	else 
	{
		if (n->left_node != NULL)
		{
			error += WriteTree (n->left_node, my_tree);
		}

		if (n->right_node != NULL)
		{
			error += WriteTree (n->right_node, my_tree);
		}
	}

	return error;
} // WriteTree

int LoadTree (Tree* t, std::string file_name)
{
	int error = 0;
	int counter = 0;
	std::string my_tree;
	std::ifstream my_file;
	my_file.open (file_name, std::ios::in);

	if (my_file.is_open() == 0)
		return 1;

	my_file >> my_tree;

	error += ReadTree (t->root, &my_tree, &counter);

	my_file.close();
	return error;
} // LoadTree

int ReadTree (TreeNode* n, std::string* my_tree, int* counter)
{
	int leaf = 1;
	int not_leaf = 0;
	int error = 0;
	std::string old_message = n->message;
	const char divider = '|';
	const char leaf_indicator = '#';

	while ((*my_tree)[*counter] != divider)
	{
		n->message += (*my_tree)[*counter];
		*counter += 1;
	}

	if (n->message.compare (old_message) == 0)
		error += 1;

	*counter += 1;

	switch ((*my_tree)[*counter]) 
	{
		case '\0': 
			break;

		case leaf_indicator :
			*counter += 1;
			n->defining_element = leaf;
			break;

		case divider :
			error += 1;
			break;

		default: 
			n->defining_element = not_leaf;
			AddLeftNode (n);
			error += ReadTree (n->left_node, my_tree, counter);
			AddRightNode (n);
			error += ReadTree (n->right_node, my_tree, counter);
	}
	
	return error;


} // ReadTree

void GenericTree (Tree* t)
{
	CreateTree (t);
	ChangeNodeData (t->root, "Uhm");
	AddLeftNode (t->root);
	AddRightNode (t->root);
	ChangeNodeData (t->root->left_node, "Hello");
	ChangeNodeData (t->root->right_node, "Now");
	AddRightNode (t->root->left_node);
	AddLeftNode (t->root->left_node);
	ChangeNodeData (t->root->left_node->right_node, "What?");
	ChangeNodeData (t->root->left_node->left_node, "Uhull");
	AddRightNode (t->root->right_node);
	AddLeftNode (t->root->right_node);
	ChangeNodeData (t->root->right_node->right_node, "What?");
	ChangeNodeData (t->root->right_node->left_node, "THISS");

} // GenericTree

} // namespace tree