#define CATCH_CONFIG_MAIN

#include "../framework/catch.h"

#include "../include/arvore.h"

namespace tree {

TEST_CASE ( "Tree Basics", "Tree operators and the tree are working right")
{
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
	}
} // TEST_CASE

} // namespace tree