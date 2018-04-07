#ifndef MP_SRC_ARVORE_H_
#define MP_SRC_ARVORE_H_

#include <string>

namespace tree {

struct TreeNode {

};


typedef struct TreeNode TreeNode;

struct Tree {
	
	TreeNode* root = NULL;
	
};

typedef struct Tree Tree;

int CreateTree (Tree* t);

} // namespace tree


#endif // MP_SRC_ARVORE_H_