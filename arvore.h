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

/*CreateTree
Contrato na especificacao: A arvore deve ser binaria.

Assertivas de entrada (requisitos): "t" deve ser sido previamente alocado.

Assertivas de saida: A saida deve ser 0 se a operacao foi computada e 1 se nao.

Interface explicita: Parametros
*/
int CreateTree (Tree* t);

/*AddRightNode
Contrato na especificacao: A arvore deve ser binaria.

Assertivas de entrada (requisitos): "n" deve ser sido previamente alocado.

Assertivas de saida: A saida deve ser 0 se a operacao foi computada e 1 se nao.

Interface explicita: Parametros
*/
int AddRightNode (TreeNode* n);

/*AddLeftNode
Contrato na especificacao: A arvore deve ser binaria.

Assertivas de entrada (requisitos): "n" deve ser sido previamente alocado.

Assertivas de saida: A saida deve ser 0 se a operacao foi computada e 1 se nao.

Interface explicita: Parametros
*/
int AddLeftNode (TreeNode* n);

/*DeleteNode
Contrato na especificacao: A arvore deve ser binaria.

Assertivas de entrada (requisitos): "n" deve ser sido previamente alocado.

Assertivas de saida: A saida deve ser 0 se a operacao foi computada e 1 se nao.

Interface explicita: Parametros
*/
int DeleteNode (TreeNode** n);

/*DeleteSubtree
Contrato na especificacao: A arvore deve ser binaria.

Assertivas de entrada (requisitos): "n" deve ser sido previamente alocado.

Assertivas de saida: A saida deve ser 0 se a operacao foi computada e outro valor positivo se nao.

Interface explicita: Parametros
*/
int DeleteSubtree (TreeNode** n);

/*DeleteTree
Contrato na especificacao: A arvore deve ser binaria.

Assertivas de entrada (requisitos): "t" deve ser sido previamente alocado.

Assertivas de saida: A saida deve ser 0 se a operacao foi computada e outro valor positivo se nao.

Interface explicita: Parametros
*/
int DeleteTree (Tree* t);

/*ChangeNodeData
Contrato na especificacao: A arvore deve ser binaria.

Assertivas de entrada (requisitos): "n" deve ser sido previamente alocado.

Assertivas de saida: Sem saida.

Interface explicita: Parametros
*/
void ChangeNodeData (TreeNode* n, std::string s);

/*SaveTree
Assertivas de entrada (requisitos): "t" e seu elemento "t->root" devem ser sido previamente alocados.

Assertivas de saida: A saida deve ser 0 se a operacao foi computada e outro valor positivo se nao.

Interface explicita: Parametros

Interface implicita: Arquivo de nome "file_name".
*/
int SaveTree (Tree* t, std::string file_name);

/*WriteTree
Contrato na especificacao: A arvore deve ser binaria.

Assertivas de entrada (requisitos): "n" deve ser sido previamente alocado.

Assertivas de saida: A saida deve ser 0 se a operacao foi computada e outro valor positivo se nao.

Assertiva de estrutura: Se o nodo nao for folha deve ter os filhos direito e esquerdo,
												caso contrario nao deve ter filhos

Interface explicita: Parametros
*/
int WriteTree (TreeNode* n, std::string* my_file);

/*LoadTree
Contrato na especificacao: A arvore deve ser binaria.

Assertivas de entrada (requisitos): "t" e seu elemento "t->root" devem ser sido previamente alocados.

Assertivas de saida: A saida deve ser 0 se a operacao foi computada e outro valor positivo se nao.

Interface explicita: Parametros

Interface implicita: Arquivo de nome "file_name".
*/
int LoadTree (Tree* t, std::string file_name);

/*ReadTree
Contrato na especificacao: A arvore deve ser binaria.

Assertivas de entrada (requisitos): "n" e "counter" devem ter sido previamente alocados e 
"counter" ser menor que o tamanho de "my_tree".

Assertivas de saida: A saida deve ser 0 se a operacao foi computada e outro valor positivo se nao.

Interface explicita: Parametros
*/
int ReadTree (TreeNode* n, std::string* my_tree, int* counter);

/*GenericTree
Contrato na especificacao: A arvore deve ser binaria.

Assertivas de entrada (requisitos): "t" deve ser sido alocado previamente.

Assertivas de saida: A saida deve ser 0 se a operacao foi computada e outro valor positivo se nao.

Interface explicita: Parametros
*/
int GenericTree (Tree* t);

} // namespace tree


#endif // MP_SRC_ARVORE_H_