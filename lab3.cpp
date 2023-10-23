// Samir Ali
// lab3.cpp
// CPSC2430
// Professor Diaz

// Purpose: Facilitaing a team to allow them to search for entities (Pets) by name, and gathering other
// information about said entity, such as age. We store the information in a BST

// Note: Possible improvements: Failsafe feature for if a Pet with the same name is being added.
// Note2: Furthest testing done: 10 pets - added at different points in the document, with multiple
// true and false searches.



#include <iostream>
#include <fstream>
#include <string>

using namespace std;


// Desc: Binary search tree (BST), holds both structs of the Pet, and the Node,
// which holds the pet object itself. Holds multiple functions such as insert, 
// search, and all 3 types of traversal.
// Pre: N/A
// Post: Creation of a BST with multiple functioning methods.
class ShelterBST {
    private:
        struct Pet {
            string name; // name of pet the object is representing
            int age; // age of pet the object is representing
        };
        struct TreeNode {
            Pet* pet; // pet pointer to the object
            TreeNode* left; // pointer to the left child
            TreeNode* right; // pointer to the right child
        };

        TreeNode* root; // initializing the root
        
        // Desc: Inserts a new pet object into the BST, determining direction using string comparison
        // Pre: Current root location in BST, and the pet object
        // Post: Returns the root location to recursively be called
        TreeNode* insert(TreeNode* root, Pet* pet) {
            if (root == nullptr) { // If this node is empty, add Pet info
                TreeNode* newNode = new TreeNode;
                newNode->pet = pet;
                newNode->left = nullptr;
                newNode->right = nullptr;
                cout << "Adding pet, name: " << pet->name << ", age: " << pet->age << endl;
                return newNode;
            }

            if (pet->name < root->pet->name) { // if the pet name comes before of after in the alphabet than the current one
                root->left = insert(root->left, pet);
            } else if (pet->name > root->pet->name) { // if name comes after
                root->right = insert(root->right, pet);
            }
            return root;
        }
        
        // Desc: Recursive method for searching for a certain pet, having to look at the specific name of the pet object
        // Pre: Current root location, and name of pet we are looking for
        // Post: Returns location of the root to grab info from.
        TreeNode* search(TreeNode* root, string name) {
            if (root == nullptr || root->pet->name == name) {
                return root;
            }

            if (name < root->pet->name) { // if/else control that checks if the culprit name is before of after, alphabetically
                return search(root->left, name);
            } else {
                return search(root->right, name);
            }
        }
        
        // Desc: Simple recursive method to call the whole BST in "inorder"
        // Pre: Current root of the BST
        // Post: No return, multiple "couts" of pet object values such as name and age
        void inorder(TreeNode* root) {
            if (root == nullptr) {
                return;
            }

            inorder(root->left);
            cout << root->pet->name << ", " << root->pet->age << endl;
            inorder(root->right);
        }
        
        // Desc: Simple recursive method to call the whole BST in "preorder"
        // Pre: Current root of the BST
        // Post: No return, multiple "couts" of pet object values such as name and age
        void preorder(TreeNode* root) {
            if (root == nullptr) {
                return;
            }

            cout << root->pet->name << ", " << root->pet->age << endl;
            preorder(root->left);
            preorder(root->right);
        }
        
        // Desc: Simple recursive method to call the whole BST in "postorder"
        // Pre: Current root of the BST
        // Post: No return, multiple "couts" of pet object values such as name and age
        void postorder(TreeNode* root) {
            if (root == nullptr) {
                return;
            }

            postorder(root->left);
            postorder(root->right);
            cout << root->pet->name << ", " << root->pet->age << endl;
        }

public:
    ShelterBST() { // contructor: initalized root
        root = nullptr;
    }
    // Desc: Calls the insert method to input a new pet object into the BST
    // Pre: Name of new pet, age of new pet
    // Post: N/A
    void insertPet(string name, int age) {
        root = insert(root, new Pet{name, age}); // initalizing new Pet within this step
    }
    // Desc: Calls the seatch method to look for a specific node with a pet with a specific name
    // and saves the result to refer to.
    // Pre: Name of the pet we are searching for
    // Post: No return, multiple "couts" of pet information, or lack thereof.
    void searchPet(string name) {
        TreeNode* result = search(root, name);
        if (result != nullptr) {
            cout << "Searching for pet with name " << result->pet->name << ": found "
            << result->pet->name << " age " << result->pet->age << "!" << endl;
        } else {
            cout << "Searching for pet with name " << name << ": no matching pet found" << endl;
        }
    }

    // Desc: Simple method calling the inorder traversal method, sending in the base root first.
    // Pre: N/A
    // Post: All of the pets with their names and ages, in alphabetical order
    void inorderDisplay() {
        cout << "In order traversal:" << endl;
        inorder(root);
    }
    
    // Desc: Simple method calling the preorder traversal method, sending in the base root first.
    // Pre: N/A
    // Post: All of the pets with their names and ages, in preorder traversal
    void preorderDisplay() {
        cout << "Pre order traversal:" << endl;
        preorder(root);
    }

    // Desc: Simple method calling the postorder traversal method, sending in the base root first.
    // Pre: N/A
    // Post: All of the pets with their names and ages, in postorder traversal
    void postorderDisplay() {
        cout << "Post order traversal" << endl;
        postorder(root);
    }
};

// Main method gathers parameters from command line, which is a file in this case.
// File is then processed and a BST is initialized. Multiple case situations are made using a 
// switch control.
int main(int argc, char* argv[]) {
    if (argc != 2) { // if the command line has more than the filename
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]); // insert the file into ifstream for scanning
    if (!inputFile.is_open()) { // if file confronts an error
        cout << "Error: Could not open the file." << endl;
        return 1;
    }

    ShelterBST tree; // initialized the BST
    char option; // var to hold case value from file
    string name; // var to hold name from file
    int age; // var to hold age from file

    while (inputFile >> option) {
        switch (option) { // multiple case options, default to using switch for ease of use.
            case 'i': // insert case
                inputFile >> name >> age;
                tree.insertPet(name, age);
                break;
            case 's': // search case
                inputFile >> name;
                tree.searchPet(name);
                break;
            case 'n': // in order traversal
                tree.inorderDisplay();
                break;
            case 'e': // pre order traversal
                tree.preorderDisplay();
                break;
            case 'o': // post order traversal
                tree.postorderDisplay();
                break;
            default: // default for if file contains an invalid char
                cout << "Invalid option: " << option << endl;
                break;
        }
    }

    inputFile.close();
    return 0;
}