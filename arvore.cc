#define ASSERT_DEBUG
#include "../include/arvore.h"

#include <stdlib.h>
#include <assert.h>
#include <iostream>

/**
		\brief Basic binary tree operations
*/

namespace tree {

/** \brief Tree root allocator
		
		The function takes one argument returning an integer value.
		\param t a Tree type pointer.
		\return The state of the operation, 0 if it was successful, 1 if it wasn't.
		\pre "t" must have been previously alocated. 
*/

int CreateTree (Tree* t) 
{
	//Assertiva de entrada
	#ifdef ASSERT_DEBUG
		assert( t != NULL ) ; // retirado se ASSERT_DEBUG não definido
	#endif

	if (t->root == NULL) // Verifica se a árvore já era existente, NULL se existente
	{
		t->root = new (std::nothrow) TreeNode();
		return 0;
	}

	else 
		return 1;
} // CreateTree

/** \brief TreeNode right son allocator

		The function takes one argument returning an integer value.
		\param n a TreeNode type pointer.
		\return The state of the operation, 0 if it was successful, 1 if it wasn't.
		\pre "n" must have been previously alocated. 
*/

int AddRightNode (TreeNode* n)
{
	//Assertiva de entrada
	#ifdef ASSERT_DEBUG
		assert( n != NULL ) ; // retirado se ASSERT_DEBUG não definido
	#endif

	const unsigned int leaf = 1;
	const unsigned int not_leaf = 0;
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

/** \brief TreeNode left son allocator

		The function takes one argument returning an integer value.
		\param n a TreeNode type pointer.
		\return The state of the operation, 0 if it was successful, 1 if it wasn't.
		\pre "n" must have been previously alocated. 
*/

int AddLeftNode (TreeNode* n)
{
	//Assertiva de entrada
	#ifdef ASSERT_DEBUG
		assert( n != NULL ) ; // retirado se ASSERT_DEBUG não definido
	#endif

	const unsigned int leaf = 1;
	const unsigned int not_leaf = 0;
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

/** \brief TreeNode deallocator

		The function takes one argument returning an integer value.
		\param n a TreeNode type pointer of pointer.
		\return The state of the operation, 0 if it was successful, 1 if it wasn't.
		\pre "n" must have been previously alocated. 
*/

int DeleteNode (TreeNode** n)
{
	//Assertiva de entrada
	#ifdef ASSERT_DEBUG
		assert( n != NULL ) ; // retirado se ASSERT_DEBUG não definido
		assert( *n != NULL ) ;
	#endif

	const unsigned int leaf = 1;
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

/** \brief TreeNode subtree deallocator

		The function takes one argument returning an integer value. \n
		It makes successive calls of function DeleteNode().
		\param n a TreeNode type pointer of pointer.
		\return The state of the operation, 0 if it was successful, another positive value if it wasn't.
		\pre "n" must have been previously alocated. 
		\sa DeleteNode()
*/

int DeleteSubtree (TreeNode** n)
{
	//Assertiva de entrada
	#ifdef ASSERT_DEBUG
		assert( n != NULL ) ; // retirado se ASSERT_DEBUG não definido
		assert( *n != NULL ) ;
	#endif

	unsigned int error = 0;

	if ((*n)->father_node != NULL) // Caso não for a raiz da árvore
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
	}

	else 
		error = -1;

	return error;
} // DeleteSubtree

/** \brief Tree deallocator

		The function takes one argument returning an integer value. \n
		It makes successive calls of function DeleteNode() and DeleteSubtree().
		\param t a Tree type pointer.
		\return The state of the operation, 0 if it was successful, another positive value if it wasn't.
		\pre "t" must have been previously alocated. 
		\sa DeleteNode() DeleteSubtree()
*/

int DeleteTree (Tree* t)
{
	//Assertiva de entrada
	#ifdef ASSERT_DEBUG
		assert( t != NULL ) ; // retirado se ASSERT_DEBUG não definido
	#endif

	unsigned int error = 0;

	if (t->root->left_node != NULL)
		error += DeleteSubtree (&(t->root->left_node));

	if (t->root->right_node != NULL)
		error += DeleteSubtree (&(t->root->right_node));

	error += DeleteNode (&(t->root));

	return error;
} // DeleteTree

/** \brief TreeNode data changer

		The function takes two arguments returning void.
		It changes the message contained in the node.
		\param n a TreeNode type pointer.
		\param s a string containing the new message.
		\pre "n" must have been previously alocated. 
*/

void ChangeNodeData (TreeNode* n, std::string s)
{
	//Assertiva de entrada
	#ifdef ASSERT_DEBUG
		assert( n != NULL ) ; // retirado se ASSERT_DEBUG não definido
	#endif

	n->message = s;
} // Change Data

/** \brief Tree saver

		The function takes two arguments. \n
		It saves the questions and answers contained in the tree in a text file calling the function WriteTree to transform the data of the tree in to a string.
		\param t a Tree type pointer.
		\param file_name a string containing the name of the text file. 
		\return The state of the operation, 0 if it was successful, another positive value if it wasn't.
		\pre "t" and its element "t->root" must have been previously alocated. 
		\sa WriteTree()
*/

int SaveTree (Tree* t, std::string file_name)
{
	//Assertiva de entrada
	#ifdef ASSERT_DEBUG
		assert( t != NULL ); // retirado se ASSERT_DEBUG não definido
		assert( t->root != NULL );
	#endif

	unsigned int error = 0;
	std::string my_tree;
	std::ofstream my_file;
	my_file.open (file_name, std::ios::out | std::ios::trunc);

	if (my_file.is_open() == 0 || my_file.fail() != 0)
		return 1;

	error += WriteTree (t->root, &my_tree);

	my_file << std::noskipws << my_tree;

	my_file.close();
	return error;
} // ChangeNodeData

/** \brief Tree writer

		The function takes two arguments returning an integer value. \n
		It converts the questions and answers contained in the tree in a string using dividers and leaf indicators. 
		\param n a TreeNode type pointer.
		\param my_tree a string pointer for the string that will contain the transformed tree. 
		\return The state of the operation, 0 if it was successful, another positive value if it wasn't.
		\pre "n" must have been previously alocated. 
*/

int WriteTree (TreeNode* n, std::string* my_tree)
{
	//Assertiva de entrada
	#ifdef ASSERT_DEBUG
		assert( n != NULL ) ; // retirado se ASSERT_DEBUG não definido
	#endif

	const unsigned int not_leaf = 0;

	//Assertiva de estrutura
	#ifdef ASSERT_DEBUG // retirado se ASSERT_DEBUG não definido
		if (n->defining_element == not_leaf)
		{
			assert( n->right_node != NULL ) ;
			assert( n->left_node != NULL ) ;
		}
		else 
		{
			assert( n->right_node == NULL ) ;
			assert( n->left_node == NULL ) ;
		}
	#endif	

	const unsigned int leaf = 1;
	unsigned int error = 0;
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

/** \brief Tree loader

		The function takes two arguments returning an integer value. \n
		It loads the questions and answers contained in a text file calling the function ReadTree to transform the data of file in to a tree.
		\param t a Tree type pointer.
		\param file_name a string containing the name of the text file. 
		\return The state of the operation, 0 if it was successful, another positive value if it wasn't.
		\pre "t" and its element "t->root" must have been previously alocated. 
		\sa ReadTree()
*/

int LoadTree (Tree* t, std::string file_name)
{
	//Assertiva de entrada
	#ifdef ASSERT_DEBUG
		assert( t != NULL ); // retirado se ASSERT_DEBUG não definido
		assert( t->root != NULL );
	#endif

	unsigned int error = 0;
	unsigned int counter = 0;
	char character;
	std::string my_tree;
	std::ifstream my_file;
	my_file.open (file_name, std::ios::in);

	if (my_file.is_open() == 0 || my_file.fail() != 0)
		return 1;

	while (my_file.get(character))
	{
		my_tree += character;
	}

	error += ReadTree (t->root, &my_tree, &counter);

	my_file.close();
	return error;
} // LoadTree

/** \brief Tree reader

		The function takes three arguments returning an integer value. \n
		It reads the questions and answers contained in a text file and transforms them in to a tree.\n
		This function only works for trees that the father node always have two sons.
		\param n a TreeNode type pointer.
		\param my_tree a string pointer for a string containing the data of the text file. 
		\param counter a integer pointer that indicates what character of the string the function is processing.
		\return The state of the operation, 0 if it was successful, another value if it wasn't.
		\pre "n" and "counter" must have been previously alocated and "counter" be smaller that "my_tree"'s size. 
		\sa AddLeftNode() AddRightNode()
*/

int ReadTree (TreeNode* n, std::string* my_tree, unsigned int* counter)
{
	//Assertiva de entrada
	#ifdef ASSERT_DEBUG
		assert( n != NULL ) ; // retirado se ASSERT_DEBUG não definido
		assert ( counter != NULL );
	#endif

	const unsigned int leaf = 1;
	const unsigned int not_leaf = 0;
	unsigned int error = 0;
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

/** \brief Generic tree builder

		The function takes one argument returning an integer value. \n
		It builds a binary tree containing seven nodes with predefined messages.
		\param t a Tree type pointer. 
		\return The state of the operation, 0 if it was successful, another value if it wasn't.
		\pre "t" must have been previously alocated. 
		\sa ChangeNodeData() AddLeftNode() AddRightNode ()
*/

int GenericTree (Tree* t)
{
	//Assertiva de entrada
	#ifdef ASSERT_DEBUG
		assert( t != NULL ) ; // retirado se ASSERT_DEBUG não definido
	#endif

	unsigned int error = 0;
	error += CreateTree (t);
	ChangeNodeData (t->root, "Voce esta pensando em uma pessoa/personagem?");

	error += AddLeftNode (t->root);
	error += AddRightNode (t->root);
	ChangeNodeData (t->root->left_node, "Voce esta pensando em um animal?");
	ChangeNodeData (t->root->right_node, "Ela existe no mundo real?");

	error += AddRightNode (t->root->left_node);
	error += AddLeftNode (t->root->left_node);
	ChangeNodeData (t->root->left_node->right_node, "Cachorro");
	ChangeNodeData (t->root->left_node->left_node, "Computador");

	error += AddRightNode (t->root->right_node);
	error += AddLeftNode (t->root->right_node);
	ChangeNodeData (t->root->right_node->right_node, "Neymar");
	ChangeNodeData (t->root->right_node->left_node, "Super-Homem");

	return error;
} // GenericTree

} // namespace tree