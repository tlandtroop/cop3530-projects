#include <string>
#include <vector>
using namespace std;

class TreeNode {
public:
  string name;
  int id;
  int height;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : name(""), id(0), left(nullptr), right(nullptr) {}
};

class BST {
public:
  TreeNode *root;

  // Destructor
  ~BST() { helperDestroy(root); }

  // Rotations
  TreeNode *right(TreeNode *node);
  TreeNode *left(TreeNode *node);
  TreeNode *rightLeft(TreeNode *node);
  TreeNode *leftRight(TreeNode *node);

  // Manipulating functions
  TreeNode *insert(TreeNode *root, string name, int id);
  TreeNode *remove(TreeNode *root, int id);
  void searchId(TreeNode *root, int id);
  void searchName(TreeNode *root, string name);

  // Printing functions
  void printInorder(TreeNode *root);
  void printPreorder(TreeNode *root);
  void printPostorder(TreeNode *root);
  void printLevelCount(TreeNode *root);
  void removeInorder(TreeNode *root, int n);

private:
  // Helper functions
  void helperIn(TreeNode *root, vector<string> &vec);
  void helperPre(TreeNode *root, vector<string> &vec);
  void helperPost(TreeNode *root, vector<string> &vec);
  int height(TreeNode *root);
  int getBalanceFactor(TreeNode *node);
  TreeNode *createNode(string name, int id);
  void helperDestroy(TreeNode *root);
};