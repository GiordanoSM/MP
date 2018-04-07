#define CATCH_CONFIG_MAIN

#include "../include/catch.h"

#include "../include/arvore.h"

namespace tree {

TEST_CASE ( "Tree Basics", "Tree operators and the tree are working right")
{
	TreeNode* n = new TreeNode();


	SECTION ( "Creating a Tree" )
	{
		Tree* t = new Tree();

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
	}
}

} // namespace tree