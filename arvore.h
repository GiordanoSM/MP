#ifndef MP_SRC_ARVORE_H_
#define MP_SRC_ARVORE_H_

#include <string>

namespace tree {

struct TreeNode {

	struct TreeNode* right_node = NULL;
	struct TreeNode* left_node = NULL;
	struct TreeNode* father_node = NULL;
	std::string message;

};

typedef struct TreeNode TreeNode;


struct Tree {
	
	TreeNode* root = NULL;
	
};

typedef struct Tree Tree;


int CreateTree (Tree* t);

int AddRightNode (TreeNode* n);

int AddLeftNode (TreeNode* n);

int DeleteNode (TreeNode** n);

int DeleteSubtree (TreeNode** n);

int DeleteTree (Tree* t);

void ChangeNodeData (TreeNode* n, std::string s);

int SaveTree (Tree* t, std::string file_name);

} // namespace tree


#endif // MP_SRC_ARVORE_H_