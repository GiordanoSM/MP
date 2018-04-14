#define CATCH_CONFIG_MAIN

#include <iostream>

#include "../framework/catch.h"
#include "../include/arvore.h"
#include "../include/jogo_interface.h"

namespace tree {

TEST_CASE ( "Tree Basics", "Tree operators and the tree are working right")
{
	int leaf = 1;
	int not_leaf = 0;
	TreeNode* n = new (std::nothrow) TreeNode();


	SECTION ( "Creating a Tree" )
	{
		Tree* t = new (std::nothrow) Tree();
		REQUIRE (t != NULL);

		SECTION ( "Creating a new tree" )
		{
			CreateTree(t);
			REQUIRE (t->root != NULL);
			delete t->root; 
		}

		SECTION ( "Tree already exists or Tree variable was not alocated" )
		{
			int error;
			CreateTree(t);
			error = CreateTree(t);
			REQUIRE (error == 1);
		}
	} // Creating a Tree

	SECTION ( "Adding a node to the tree" )
	{
		SECTION ( "Right node" )
		{
			int error;

			SECTION ( "New node" )
			{
				error = AddRightNode (n);
				REQUIRE (error == 0);
				REQUIRE (n->defining_element == not_leaf);
				REQUIRE (n->right_node->father_node == n);
				REQUIRE (n->right_node->defining_element == leaf);
				delete n->right_node;
			}

			SECTION ( "Node already exists" )
			{
				AddRightNode (n);
				error = AddRightNode (n);
				REQUIRE (error == 1);
			}
		} // Right Node

		SECTION ( "Left node" )
		{	
			int error;

			SECTION ( "New node" )
			{
				error = AddLeftNode (n);
				REQUIRE (error == 0);
				REQUIRE (n->defining_element == not_leaf);
				REQUIRE (n->left_node->father_node == n);
				REQUIRE (n->left_node->defining_element == leaf);
				delete n->left_node;
			}

			SECTION ( "Node already exists" )
			{
				AddLeftNode (n);
				error = AddLeftNode (n);
				REQUIRE (error == 1);
			}
		} // Left Node
	} // Adding a node

	SECTION ( "Deleting a node" )
	{
		int error;
		TreeNode* parent = new (std::nothrow) TreeNode();

		SECTION ( "Without sons" )
		{
			DeleteNode (&parent);
			REQUIRE (parent == NULL);
		}

		SECTION ( "With sons" )
		{
			AddLeftNode (parent);
			error = DeleteNode (&parent);
			REQUIRE (error == 1);
			REQUIRE (parent != NULL);
			delete parent->left_node;
		}

		SECTION ( "With a father node" )
		{
			AddLeftNode (parent);
			DeleteNode (&parent->left_node);
			REQUIRE (parent->defining_element == leaf);
			delete parent->left_node;
		}

	} // Deleting a node

	SECTION ( "Deleting a subtree" )
	{
		int error;
		TreeNode* parent = new (std::nothrow) TreeNode();
		AddLeftNode (parent);
		AddRightNode (parent->left_node);


		SECTION ( "Not the root of the tree" )
		{
			error = DeleteSubtree (&parent->left_node);
			REQUIRE (error == 0);
		}

		SECTION ( "The root of the tree" )
		{
			error = DeleteSubtree (&parent);
			REQUIRE (error == -1);
		}
		//delete parent->left_node->right_node;
		delete parent->left_node;
		delete parent;
	} // Deleting a subtree

	SECTION ( "Deleting the tree" )
	{
		int error;
		Tree t;
		CreateTree (&t);
		AddLeftNode (t.root);
		AddRightNode (t.root->left_node);

		error = DeleteTree (&t);

		REQUIRE (error == 0); 
		REQUIRE (t.root == NULL);
	} // Deleting the tree

	SECTION ( "Changing the node's data" )
	{
		int error;
		std::string s = "The color of the object is blue?";
		ChangeNodeData (n, s);

		error = (n->message != s);

		REQUIRE (error == 0);
	} // Changing data

	SECTION ( "Tree in file" )
	{
		Tree t;
		GenericTree (&t);
		std::string file_name = "name_file.txt";

		SECTION ( "Saving the tree" )
		{
			int error;

			SECTION ( "Writing the tree" )
			{
				std::string my_tree;
				error = WriteTree (t.root, &my_tree);
				REQUIRE (error == 0);
			}

			error = SaveTree (&t, file_name);

			REQUIRE (error == 0);
		} // Saving tree

		SECTION ( "Loading the tree" )
		{
			int error;
			Tree t2;
			CreateTree (&t2);

			SECTION ( "Reading the tree" )
			{
				int counter = 0;
				std::string my_tree;
				std::string my_tree_2;

				WriteTree (t.root, &my_tree);
				error = ReadTree (t2.root, &my_tree, &counter);
				REQUIRE (error == 0);

				WriteTree (t2.root, &my_tree_2);
				REQUIRE (my_tree.compare(my_tree_2) == 0);
			}

			error = LoadTree (&t, file_name);
			REQUIRE (error == 0);
			DeleteTree (&t2);
		} // Loading tree

		DeleteTree (&t);
	} //Tree in file

	delete n;
} // TEST_CASE

TEST_CASE ( "Game Basics", "Tree operators with user interface")
{
	SECTION ( "Starting the tree" )
	{
		int error;
		Tree t;

		SECTION ( "Loading the tree" )
		{
			std::cout << "-------------- TEST: Do it right using (Arquivo)--------------\n\n";
			error = StartTree (&t);
			REQUIRE (error == 0);
			DeleteTree (&t);

			SECTION ( "Wrong file" )
			{
			std::cout << "\n-------------- TEST: Write wrong file name (Arquivo)--------------\n\n";
			error = StartTree (&t);
			REQUIRE (error == 1);
			DeleteTree (&t);
			}
		}

		SECTION ( "Using default tree" )
		{
			std::cout << "-------------- TEST: Do it right using (Default)--------------\n\n";
			error = StartTree (&t);
			REQUIRE (error == 0);
			DeleteTree (&t);
		}

		SECTION ( "Wrong command" )
		{
			std::cout <<  "-------------- TEST: Write wrong command --------------\n\n";
			error = StartTree (&t);
			REQUIRE (error == -1);
		}
	} // Starting tree

	SECTION ( "Interpreting answers" )
	{
		int error;
		Tree t;
		GenericTree (&t);

		SECTION ( "To questions" )
		{
			TreeNode* current_location;

			current_location = t.root;
			error = AnswerInterpreter (&current_location, "Sim" );
			REQUIRE (error == 0);
			REQUIRE (current_location == t.root->right_node);

			current_location = t.root;
			error = AnswerInterpreter (&current_location, "Nao" );
			REQUIRE (error == 0);
			REQUIRE (current_location == t.root->left_node);

			current_location = t.root;
			error = AnswerInterpreter (&current_location, "Outra resposta" );
			REQUIRE (error == 1);
			REQUIRE (current_location == t.root);
		}

		DeleteTree (&t);
	}

} // TEST_CASE

} // namespace tree