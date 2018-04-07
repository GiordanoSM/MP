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
	}
}

} // namespace tree
