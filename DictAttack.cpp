/*==================================================================================
 Name          : DictAttack.cpp
 Author        : Team #2: Chad Netwig, Parker Bjur, Damien Diaz, and Syedali Khan
 Last Updated  : 05/13/2021
 Project       : Term Project for CS-265-70
 Description   : This program will prompt the user for a three letter password
               : string in lower-case. A Binary Search Tree holding the alphabet
               : will be traversed to build up to 26^3 combinations in order to do
               : a brute-force attack on the password until it is found.
==================================================================================
*/


    // UPDATE: 05-13-2021
    //
    // To be implemented:
    //
    // 1. Do a compare against the user-inputed password in the "k" for loop
    //    DONE 5/12/21 - CLN
    // 2. Instead of specifying the array as [25], use the treeSize int value to make the code more flexible
    //    DONE 5/13/21 - CLN
    // 3. Parker to create class to take string value and convert it into decimal integers and return array
    // 4. Damien and Ali to test functionality



#include <iostream>

using namespace std;

static int pwIterations  = 0;    // keeps count of how many iterations it took to crack the password

/* Setup BinaryNodes Structure for left & right children and their parent */
struct Node
{
    int key;
    struct Node *left, *right, *parent;

    ~Node() {}  // destructor
};

/*This is an implementation of std::set class using a Binary Search Tree data structure
                                                                                        */
class Set_BST
{
public:

// Setup newNode structure
struct Node *newNode(int item)
{
    struct Node *temp = new Node;
    temp->key = item;
    temp->left = temp->right = NULL;
    temp->parent = NULL;
    return temp;
}

// this function performs an  infix traversal of BST and displays the output of the node's key value
void infix(struct Node *root, int (&myArray)[25])
{
static int i;

    if (root != NULL)
    {
        infix(root->left, myArray);
        // cout << " Node # " << root->key << endl;
        //debug: cout << "Key: " << char(root->key) << endl;

        myArray[i] = root->key;

        //debug: cout << "val of arr is : " << myArray[i] << endl;
        i++;
        infix(root->right, myArray);
    }
}

// member function to insert a new node
struct Node *insert(struct Node* node, int key)
{
    // If the tree is empty, return a new Node
    if (node == NULL) return newNode(key);

   // Else, traverse tree
    if (key < node->key)
    {
        Node *leftChild = insert(node->left, key);
        node->left  = leftChild;

        // Set parent of root of left subtree
        leftChild->parent = node;
    }
    else if (key > node->key)
    {
        Node *rightChild = insert(node->right, key);
        node->right  = rightChild;

        // Set parent of root of right subtree
        rightChild->parent = node;
    }

    /* return the (unchanged) Node pointer */
    return node;
}


// this is a BST implementation of the std::set.empty() member function
bool isEmpty( Node *tree )
{
    return tree == nullptr;
}

// used for Traversal
bool isLeaf( Node *tree )
{
    return tree->left == nullptr && tree->right == nullptr;
}

// this is a BST implementation of the std::set.size() member function
int size( Node *tree )
{
    if ( !isEmpty( tree ))
        return 1 + size( tree->left ) + size( tree->right );
    else return 0;
}


}; // end Set_BST class


bool passwordCrack(string pwCrack, string pwUser)
{

    // cout << "\npw test is: " << pw << endl;
    if (pwCrack == pwUser){

        cout << "\n\nPasword cracked!" << endl;
        cout << "Brute-force attempts: " << pwIterations << endl;
        cout << "The password is: " << pwCrack << endl;
        return 1;   // return true (pw found)
    }

return 0;
}

int testPassword(int (&myArr)[25], string pwTest, string password)
{
    int i, j, k;
    string disp;

        cout << "\nDisplay password crack attempts? [y/n]: ";
        cin >> disp;
        cout << "\nStarting Brute-Force Attack on the Password..." << endl;

        // loop through all possible three letter combinations using embedded for loops
        for (i = 0; i <= 25; i++) {

             for (j = 0; j <= 25; j++) {

                for (k=0; k <= 25; k++) {
                    if (disp == "y" || disp == "Y") { cout << char(myArr[i]) << char(myArr[j]) << char(myArr[k]) << ", "; }

                    // build pwTest string
                    pwTest.clear();
                    pwTest.push_back(myArr[i]);
                    pwTest.push_back(myArr[j]);
                    pwTest.push_back(myArr[k]);
                    pwIterations++;
                    // check user-entered password against iteration. If found break out
                    if (passwordCrack (pwTest, password)) { return 1; }
                } // end k for
             } // end j for
        } //end i for
        cout << "\n\nUnable to crack password!" << endl;
        cout << "Please make sure that the password entered is exactly three lower-case letters" << endl;
        return 0;
} // end testPassword



int main()
{
 /*

    DictAttack

 */

 //const int TREE_SIZE = 0;

string password;                // holds user-entered password
string pwTest = "";

 /*
   Create BST Tree with following structure

              97
                \
                98
                 \
                  99
                   \
                    100
                      \
                       ...
                        \
                        122

                        This holds the ascii decimal for a - z (lower-case)
                                    */

    struct Node *myTree = NULL;     // create myTree pointer to Node structure and set the root to NULL

    Set_BST MyBST;                  // create object myBST from Set_BST class

    /*  build tree with alphabet in lowercase using ascii decimal */
    myTree = MyBST.insert(myTree, 97);
    for (int i = 98; i <= 122; i++) {

        MyBST.insert(myTree, i);
    }


    const int TREE_SIZE = MyBST.size(myTree);  // get treeSize
    cout << "Tree size is: " << TREE_SIZE;

    //const int TREE_SIZE = 25;

    int arr[25];
    MyBST.infix(myTree, arr);       // infix traversal stores values in array along the way


    // Prompt user for a 3-letter password
    cout << "\nPlease enter a password of three lower-case characters (no special characters): ";
    cin >> password;


    /* 1. Take array that was built from tree -- which is essentially the lowercase alphabet -- and dump all combinations of a string
          of length 3 to the screen.
       2. Along the way, brute-force check iterations against the user-entered password and display the cracked password if found */


    testPassword(arr, pwTest, password);


    return 0;
}
