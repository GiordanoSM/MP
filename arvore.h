#ifndef MP_SRC_ARVORE_H_
#define MP_SRC_ARVORE_H_

#include <string>
#include <fstream>

namespace tree {

/** \brief Tree node
		It contains the necessary information of a node of a tree.
*/

struct TreeNode {
	/** TreeNode pointer to its right son. */
	struct TreeNode* right_node = NULL; 
	/** TreeNode pointer to its left son. */
	struct TreeNode* left_node = NULL; 
	/** TreeNode pointer to its father node. */
	struct TreeNode* father_node = NULL; 
	/** String that can be a question or a answer depending on the defining_element.*/
	std::string message; 
	/** Integer that can be 1 (leaf) or 0 (not leaf).*/ // Pode adquirir o valor folha (1) ou o valor nao_folha (2)
	int defining_element; 

};

/** \brief Type that refers to the struct TreeNode. */

typedef struct TreeNode TreeNode; 

/** \brief Tree
		It contains the necessary information to define a tree, the root.
*/

struct Tree {
	/** TreeNode pointer to its root node*/
	TreeNode* root = NULL; 
	
};

/** \brief Type that refers to the struct Tree. */

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

int LoadTree (Tree* t, std::string file_name);

int ReadTree (TreeNode* n, std::string* my_tree, int* counter);

int GenericTree (Tree* t);

} // namespace tree


#endif // MP_SRC_ARVORE_H_