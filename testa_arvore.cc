#define CATCH_CONFIG_MAIN

#include "../framework/catch.h"
#include "../include/arvore.h"

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
		}

		SECTION ( "With a father node" )
		{
			AddLeftNode (parent);
			error = DeleteNode (&parent->left_node);
			REQUIRE (parent->defining_element == leaf);
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

	SECTION ( "Saving the tree" )
	{
		int error;
		Tree t;
		CreateTree (&t);
		AddLeftNode (t.root);
		AddRightNode (t.root->left_node);
		std::string file_name = "name_file.txt";

		SECTION ( "Writing the tree" )
		{
			std::string my_tree;
			error = WriteTree (t.root, my_tree);
			REQUIRE (error == 0);
		}

		error = SaveTree (&t, file_name);

		REQUIRE (error == 0);
	} // Saving tree

} // TEST_CASE

} // namespace tree