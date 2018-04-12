#ifndef MP_SRC_ARVORE_H_
#define MP_SRC_ARVORE_H_

#include <string>
#include <fstream>

namespace tree {

struct TreeNode {

	struct TreeNode* right_node = NULL;
	struct TreeNode* left_node = NULL;
	struct TreeNode* father_node = NULL;
	std::string message;
	int defining_element; // Pode adquirir o valor folha (1) ou o valor nao_folha (2)

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

int WriteTree (TreeNode* n, std::string* my_file);

} // namespace tree


#endif // MP_SRC_ARVORE_H_