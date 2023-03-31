#include "bst.h"
#include <iostream>
#include <vector>
#include <regex>
#include <sstream>
#include <stack>
using namespace std;

// Helpers
void BST::helperIn(TreeNode *root, vector<string> &vec) {
  // Base Case
  if (root == nullptr) {
    return;
  }
  // Recursively pushes values to vectors in inorder traversal form
  helperIn(root->left, vec);
  vec.push_back(root->name);
  helperIn(root->right, vec);
}

void BST::helperPre(TreeNode *root, vector<string> &vec) {
  // Base Case
  if (root == nullptr) {
    return;
  }
  // Recursively pushes values to vectors in preorder traversal form
  vec.push_back(root->name);
  helperPre(root->left, vec);
  helperPre(root->right, vec);
}

void BST::helperPost(TreeNode *root, vector<string> &vec) {
  // Base Case
  if (root == nullptr) {
    return;
  }
  // Recursively pushes values to vectors in postorder traversal form
  helperPost(root->left, vec);
  helperPost(root->right, vec);
  vec.push_back(root->name);
}

int BST::height(TreeNode *root) {
  // Base Case
  if (root == nullptr) {
    return 0;
  } else {
    int left = height(root->left);
    int right = height(root->right);
    // Calculates the maximum height of the tree
    return max(left, right) + 1;
  }
}

int BST::getBalanceFactor(TreeNode *node) {
  // If tree is empty, balance factor is 0
  if (node == nullptr) {
    return 0;
  }
  // Calculates the balance factor
  return height(node->left) - height(node->right);
}

TreeNode *BST::createNode(string name, int id) {
  // Initializes a new node
  TreeNode *node = new TreeNode();
  node->id = id;
  node->name = name;
  node->left = nullptr;
  node->right = nullptr;
  node->height = 1;

  return node;
}

void BST::helperDestroy(TreeNode *root) {
  if (root) {
    helperDestroy(root->left);
    helperDestroy(root->right);
    delete root;
  }
}

// Rotations
TreeNode *BST::right(TreeNode *root) {
  // In the left left case, do a right rotation
  TreeNode *grandchild = root->left->right;
  TreeNode *newParent = root->left;
  newParent->right = root;
  root->left = grandchild;
  return newParent;
}

TreeNode *BST::left(TreeNode *root) {
  // In the right right case, do a left rotation
  TreeNode *grandchild = root->right->left;
  TreeNode *newParent = root->right;
  newParent->left = root;
  root->right = grandchild;
  return newParent;
}

TreeNode *BST::rightLeft(TreeNode *root) {
  // In the right left case, do a right left rotation
  root->right = right(root->right);
  return left(root);
}

TreeNode *BST::leftRight(TreeNode *root) {
  // In the left right case, do a left right rotation
  root->left = left(root->left);
  return right(root);
}

// Manipulative Functions
TreeNode *BST::insert(TreeNode *root, string name, int id) {
  // If there are no nodes, make new node with given name and id
  if (root == nullptr) {
    cout << "successful" << endl;
    return createNode(name, id);
  }

  // If id is less than root's id, go down left subtree, otherwise go down right
  if (id < root->id) {
    root->left = insert(root->left, name, id);
  } else if (id > root->id) {
    root->right = insert(root->right, name, id);
  }

  // Re-check the height before the rotation
  root->height = height(root);
  // Get balance factor for rotation
  int balanceFactor = getBalanceFactor(root);

  // Left Left case
  if (balanceFactor == 2 && id < root->left->id) {
    return right(root);
  }
  // Right Right case
  if (balanceFactor == -2 && id > root->right->id) {
    return left(root);
  }

  // Left Right case
  if (balanceFactor == 2 && id > root->left->id) {
    return leftRight(root);
  }

  // Right Left case
  if (balanceFactor == -2 && id < root->right->id) {
    return rightLeft(root);
  }

  return root;
}

TreeNode *BST::remove(TreeNode *root, int id) {
  // If there are no nodes, return null
  if (root == nullptr) {
    cout << "unsuccessful" << endl;
    return root;
  }
  // If id is less than root's id, go down left subtree
  else if (id < root->id) {
    root->left = remove(root->left, id);
  }
  // If id is greater than root's id, go down right subtree
  else if (id > root->id) {
    root->right = remove(root->right, id);
  }
  // If we are on the correct node, check for the number of children
  else {
    // If there are no children, delete root
    if (root->left == nullptr && root->right == nullptr) {
      delete root;
      cout << "successful" << endl;
      return nullptr;
    }
    // If there is one child, delete other child
    else if (root->left == nullptr) {
      TreeNode *temp = root->right;
      delete root->right;
      cout << "successful" << endl;
      return temp;
    }
    // If there is one child, delete other child
    else if (root->right == nullptr) {
      TreeNode *temp = root->left;
      delete root->left;
      cout << "successful" << endl;
      return temp;
    }
    // If there are two children, get preorder successor and replace root with
    // it, then delete node.
    else {
      TreeNode *temp = root->left;
      while (temp && temp->right != nullptr) {
        temp = temp->right;
      }
      root->id = temp->id;
      root->name = temp->name;

      root->left = remove(root->left, temp->id);
    }
  }
  // Re-check height after deletion
  root->height = height(root);
  return root;
}

void BST::searchId(TreeNode *root, int id) {
  // If there are no nodes, return unsuccessful, otherwise recursively check for
  // id
  if (root == nullptr) {
    cout << "unsuccessful" << endl;
  } else if (id == root->id) {
    cout << root->name << endl;
  } else if (root->id < id) {
    searchId(root->right, id);
  } else if (root->id > id) {
    searchId(root->left, id);
  }
}

void BST::searchName(TreeNode *root, string name) {
  vector<int> ids;
  stack<TreeNode *> stack;
  stack.push(root);

  // Iterate through stack and push the values of the tree in preorder form
  while (!stack.empty()) {
    TreeNode *current = stack.top();
    stack.pop();
    if (current != nullptr) {
      if (name == current->name) {
        ids.push_back(current->id);
      }
      stack.push(current->right);
      stack.push(current->left);
    }
  }
  // If there are values in the vector, print them on separate lines
  if (ids.size() != 0) {
    for (int i = 0; i < ids.size(); i++) {
      cout << ids[i] << endl;
    }
  } else {
    cout << "unsuccessful" << endl;
  }
}

// Printing Functions
void BST::printInorder(TreeNode *root) {
  // Use helper function to populate vector with names
  vector<string> vec;
  helperIn(root, vec);

  // Print values in vector with a comma before each except for first.
  bool first = true;
  for (int i = 0; i < vec.size(); i++) {
    if (first) {
      cout << vec[i];
    } else {
      cout << ", " << vec[i];
    }
    first = false;
  }
}

void BST::printPreorder(TreeNode *root) {
  // Use helper function to populate vector with names
  vector<string> vec;
  helperPre(root, vec);

  // Print values in vector with a comma before each except for first.
  bool first = true;
  for (int i = 0; i < vec.size(); i++) {
    if (first) {
      cout << vec[i];
    } else {
      cout << ", " << vec[i];
    }
    first = false;
  }
}

void BST::printPostorder(TreeNode *root) {
  // Use helper function to populate vector with names
  vector<string> vec;
  helperPost(root, vec);

  // Print values in vector with a comma before each except for first.
  bool first = true;
  for (int i = 0; i < vec.size(); i++) {
    if (first) {
      cout << vec[i];
    } else {
      cout << ", " << vec[i];
    }
    first = false;
  }
}

void BST::printLevelCount(TreeNode *root) {
  // If tree is empty, print 0 for level count, otherwise print the max height
  if (root == nullptr)
    cout << 0;
  else {
    cout << height(root);
  }
}

// Other
void BST::removeInorder(TreeNode *root, int n) {
  // Stack to hold inorder values
  stack<TreeNode *> stack;
  // Temp pointer to traverse tree
  TreeNode *temp = root;
  // Counter to check against n
  int counter = 0;

  // Iterate through tree and check if counter is equal to n, if so delete
  while (!stack.empty() || temp != nullptr) {
    while (temp != nullptr) {
      stack.push(temp);
      temp = temp->left;
    }
    temp = stack.top();

    if (counter == n) {
      remove(root, temp->id);
    }

    counter++;
    stack.pop();
    temp = temp->right;
  }
}

int main() {
  BST t;

  // Gets the number of following commands
  string numCommands;
  getline(cin, numCommands);
  int numberCommands = stoi(numCommands);

  // Used to check against name given
  regex valid("^[a-zA-Z]+$");

  // Go through amount of commands
  for (int i = 0; i < numberCommands; i++) {
    string line;
    getline(cin, line);

    // istringstream object to read values
    istringstream in(line);

    // Gets the command (insert, remove, search)
    string command;
    in >> command;

    if (command == "insert") {
      in >> ws;

      // Gets the quotation before and after the name
      char quote;
      in.get(quote);

      // Read until the next quotation
      string next;
      getline(in, next, '"');

      in.get(quote);

      // Sets name equal to the value read in next
      string name;
      name = next;

      // If the name is valid, get id.
      if (regex_match(name, valid)) {
        in >> ws;

        getline(in, next);

        // Convert id to integer
        int id = stoi(next);

        // If the id is the correct length, insert, otherwise print unsuccessful
        if (next.length() == 8) {
          t.root = t.insert(t.root, name, id);
        } else {
          cout << "unsuccessful" << endl;
        }
      } else {
        cout << "unsuccessful" << endl;
      }
    } else if (command == "remove") {
      // Get whitespace
      in >> ws;

      string next;
      getline(in, next);

      // Convert id to integer
      int id = stoi(next);
      // If the id is the correct length, remove, otherwise print unsuccessful
      if (next.length() == 8) {
        t.root = t.remove(t.root, id);
      } else {
        cout << "unsuccessful" << endl;
      }
    } else if (command == "search") {
      // Get whitespace
      in >> ws;

      // Gets the next character
      char quote = '"';
      in.get(quote);

      // If next character is a quote, search by name
      if (quote == '"') {

        // Read the name up to the next quote
        string next;
        getline(in, next, '"');

        in.get(quote);

        // Set the name to the value in next
        string name;
        name = next;

        // If the name is valid, search for it, otherwise print unsuccessful
        if (regex_match(name, valid)) {
          t.searchName(t.root, name);
        } else {
          cout << "unsuccessful" << endl;
        }
      }
      // If next character is not a quotation, search by id
      else {
        // Get the values of the id plus the value stored in quote
        string next;
        in >> next;
        next.insert(0, 1, quote);

        // Convert id to integer
        int id = stoi(next);

        // If id is correct length, search by id, otherwise print unsuccessful
        if (next.length() == 8) {
          t.searchId(t.root, id);
        } else {
          cout << "unsuccessful" << endl;
        }
      }
    } else if (command == "printInorder") {
      // Print tree's inorder traversal
      t.printInorder(t.root);
      cout << endl;
    } else if (command == "printPreorder") {
      // Print tree's preorder traversal
      t.printPreorder(t.root);
      cout << endl;
    } else if (command == "printPostorder") {
      // Print tree's postorder traversal
      t.printPostorder(t.root);
      cout << endl;
    } else if (command == "printLevelCount") {
      // Print tree's level
      t.printLevelCount(t.root);
      cout << endl;
    } else if (command == "removeInorder") {
      // Get whitespace
      in >> ws;

      // Gets the value for n
      string next;
      getline(in, next);

      int n = stoi(next);
      // If n is a single value, remove that nth node
      if (next.length() == 1) {
        t.removeInorder(t.root, n);
      }
    } else {
      cout << "Error" << endl;
    }
  }
  t.~BST();
}