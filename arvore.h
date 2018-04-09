#ifndef MP_SRC_ARVORE_H_
#define MP_SRC_ARVORE_H_

#include <string>

namespace tree {

struct TreeNode {

	struct TreeNode* right_node = NULL;
	struct TreeNode* left_node = NULL;

};

typedef struct TreeNode TreeNode;


struct Tree {
	
	TreeNode* root = NULL;
	
};

typedef struct Tree Tree;


int CreateTree (Tree* t);

int AddRightNode (TreeNode* n);

int AddLeftNode (TreeNode* n);

void DeleteNode (TreeNode** n);

} // namespace tree


#endif // MP_SRC_ARVORE_H_