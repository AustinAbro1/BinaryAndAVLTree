#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

//Austin Abro

//AVL Appears at the bottom of output

const int max_rows = 20;
const int max_coloumns = 120;
int insertOperations;
int totalInsertOperations;
int spacing = 0;
int searchOperations = 0;
int totalSearchOperations;
int deleteOperations;
int totalDeleteOperations;
int creationOperations;
int totalOperations;

int AVLTreeCreationOperations;
int AVLdeleteOperations = 1;
int totalAVLdeleteOperations;
int AVLinsertOperations = 1;
int totalAVLinsertOperations;
int AVLsearchOperations = 1;
int totalAVLsearchOperations;
int totalAVLOperations;

ofstream outputFile("TestCase51BST.txt");

//Function to insert a node into the tree
void insertNode(int arr[][max_coloumns], int countArr[][max_coloumns], int rootIndex, int input, int rowIndex, int spacing) {
    //If the current position in the tree is empty
    if (arr[rowIndex][rootIndex] == 0) {
        //Insert the input value and set the count of the number to 1
        arr[rowIndex][rootIndex] = input;
        countArr[rowIndex][rootIndex] = 1;
    }
    //If the input is less than the current node's value
    else if (input < arr[rowIndex][rootIndex]) {
        //Recursively insert to the left subtree
        insertNode(arr, countArr, rootIndex - spacing, input, rowIndex + 2, (spacing / 2) + 1);
    }
    //If the input is greater than the current node's value
    else if (input > arr[rowIndex][rootIndex]) {
        //Recursively insert to the right subtree
        insertNode(arr, countArr, rootIndex + spacing, input, rowIndex + 2, (spacing / 2) + 1);
    }
    //If the input is equal to the current node's value
    else if (input == arr[rowIndex][rootIndex]) {
        //Increment the count for that node
        countArr[rowIndex][rootIndex]++;
    }

    creationOperations++;
    insertOperations++;
}


//Function to delete a node in a BST
bool deleteNode(int arr[][max_coloumns], int countArr[][max_coloumns], int rootIndex, int input, int rowIndex, int spacing) {
    if (arr[rowIndex][rootIndex] == 0 && arr[rowIndex + 2][rootIndex - spacing] == 0 && arr[rowIndex + 2][rootIndex + spacing] == 0
        && arr[rowIndex + 4][rootIndex - (spacing / 2) + 1] == 0 && arr[rowIndex + 4][rootIndex + (spacing / 2) + 1]) {
        //Node with the input is not found
        return false;
    }
    else if (arr[rowIndex][rootIndex] == 0 && arr[rowIndex + 2][rootIndex - spacing] == 0 && arr[rowIndex + 2][rootIndex + spacing] == 0) {
        return true;
    }
    else if (arr[rowIndex][rootIndex] == 0) {
        return true;
    }

    if (input < arr[rowIndex][rootIndex]) {
        deleteOperations++;
        return deleteNode(arr, countArr, rootIndex - spacing, input, rowIndex + 2, (spacing / 2) + 1);
    }
    else if (input > arr[rowIndex][rootIndex]) {
        deleteOperations++;
        return deleteNode(arr, countArr, rootIndex + spacing, input, rowIndex + 2, (spacing / 2) + 1);
    }
    else {
        //Node with the input is found, handle deletion
        if (countArr[rowIndex][rootIndex] > 1) {
            //If the node is a twin node, decrement the count
            if (arr[rowIndex][rootIndex] == arr[rowIndex - 2][rootIndex - spacing]) {
                deleteOperations++;
                arr[rowIndex][rootIndex] = 0;
            }
            else {
                deleteOperations++;
                countArr[rowIndex][rootIndex] -= 1;
            }
        }
        else {
            //If the node is not a twin node, delete the node

            //Node with no child
            if (arr[rowIndex + 2][rootIndex - spacing] == 0 && arr[rowIndex + 2][rootIndex + spacing] == 0) {
                int temp = arr[rowIndex][rootIndex];
                if (input == temp) {
                    deleteOperations++;
                    arr[rowIndex][rootIndex] = 0;
                    countArr[rowIndex][rootIndex] = 0;
                }
            }
            //Both Children are present
            else if (arr[rowIndex + 2][rootIndex - spacing] != 0 && arr[rowIndex + 2][rootIndex + spacing] != 0) {
                int temp = arr[rowIndex][rootIndex];
                arr[rowIndex][rootIndex] = arr[rowIndex + 2][rootIndex + spacing];
                countArr[rowIndex][rootIndex] = countArr[rowIndex + 2][rootIndex + spacing];
                temp = arr[rowIndex + 2][rootIndex + spacing];
                deleteOperations++;
                return deleteNode(arr, countArr, rootIndex + spacing, temp, rowIndex + 2, (spacing / 2) + 1);
            }
            else if (arr[rowIndex + 2][rootIndex - spacing] == 0) {
                //Only right child is present
                int temp = arr[rowIndex][rootIndex];
                arr[rowIndex][rootIndex] = arr[rowIndex + 2][rootIndex + spacing];
                countArr[rowIndex][rootIndex] = countArr[rowIndex + 2][rootIndex + spacing];
                arr[rowIndex + 2][rootIndex + spacing] = 0;
                deleteOperations++;
                return deleteNode(arr, countArr, rootIndex + spacing, temp, rowIndex + 2, (spacing / 2) + 1);
            }
            else if (arr[rowIndex + 2][rootIndex + spacing] == 0) {
                //Only left child is present
                int temp = arr[rowIndex][rootIndex];
                arr[rowIndex][rootIndex] = arr[rowIndex + 2][rootIndex - spacing];
                countArr[rowIndex][rootIndex] = countArr[rowIndex + 2][rootIndex - spacing];
                arr[rowIndex + 2][rootIndex - spacing] = 0;
                deleteOperations++;
                return deleteNode(arr, countArr, rootIndex + spacing, temp, rowIndex + 2, (spacing / 2) + 1);

            }
        }

        return true;
        //Deletion was successful
    }
}

bool searchNode(int arr[][max_coloumns], int countArr[][max_coloumns], int rootIndex, int input, int rowIndex, int spacing) {
    if (arr[rowIndex][rootIndex] == 0 && (input != 0)) {
        return false;
    }

    if (input < arr[rowIndex][rootIndex]) {
        searchOperations++;
        return searchNode(arr, countArr, rootIndex - spacing, input, rowIndex + 2, (spacing / 2) + 1);
    }
    else if (input > arr[rowIndex][rootIndex]) {
        searchOperations++;
        return searchNode(arr, countArr, rootIndex + spacing, input, rowIndex + 2, (spacing / 2) + 1);
    }
    else if (input == arr[rowIndex][rootIndex]) {
        return true;
    }

    //If none of the above conditions match, return false
    return false;
}



//Function to find the lowest row with a non-zero element in the tree to obtain height of tree
int heightFind(int arr[][max_coloumns]) {
    //Traverse the tree from the bottom to the top
    for (int i = max_rows - 1; i >= 0; --i) {
        for (int j = 0; j < max_coloumns; ++j) {
            //If a non-zero element is found, return the row index
            if (arr[i][j] != 0) {
                return i / 2; //Since rows are being incremented by two
            }
        }
    }
    return -1; //No row with non-zero element found
}

#define seperation 12

class avlTreeNode {
public:
    int value;
    int count;
    avlTreeNode* left;
    avlTreeNode* right;

    //Default constructor
    avlTreeNode() {
        value = 0;
        left = NULL;
        right = NULL;
    }

    avlTreeNode(int v) {
        value = v;
        left = NULL;
        right = NULL;
    }
};

class AVLTree {
public:
    avlTreeNode* root;
    AVLTree()
    {
        root = NULL;
    }
    bool isTreeEmpty()
    {
        if (root == NULL) {
            return true;
        }
        else {
            return false;
        }
    }

    int AVLHeight(avlTreeNode* r) {
        if (r == NULL)
            return -1;
        else {
            //Get height of each subtree for AVL tree
            int leftHeight = AVLHeight(r->left);
            int rightHeight = AVLHeight(r->right);

            if (leftHeight < rightHeight)
                return(rightHeight + 1);
            else
                return (leftHeight + 1);
        }
    }

    //Get balance factor for node
    int getBalanceFactor(avlTreeNode* n) {
        if (n == NULL)
            return -1;
        return AVLHeight(n->left) - AVLHeight(n->right);
    }

    avlTreeNode* rightRotate(avlTreeNode* y) {
        AVLTreeCreationOperations++;
        avlTreeNode* x = y->left;
        avlTreeNode* z = x->right;

        //Does rotation
        x->right = y;
        y->left = z;

        return x;
    }

    avlTreeNode* leftRotate(avlTreeNode* x) {
        AVLTreeCreationOperations++;
        avlTreeNode* y = x->right;
        avlTreeNode* z = y->left;

        //Does rotation
        y->left = x;
        x->right = z;

        return y;
    }


    void printAVLTree(avlTreeNode* r, int space) {
        if (r == NULL)
            return;
        space += seperation;
        printAVLTree(r->right, space);
        cout << endl;
        outputFile << endl;
        for (int i = seperation; i < space; i++) {
            cout << " ";
            outputFile << " ";
        }
        if (r->count >= 1) {
            r->count += 1;
            outputFile << r->value << "-" << r->count << "\n";
            cout << r->value << "-" << r->count << "\n";
            r->count -= 1;
        }
        else {
            outputFile << r->value << "\n";
            cout << r->value << "\n";
        }
        printAVLTree(r->left, space);
    }

    avlTreeNode* lowestNode(avlTreeNode* node) {
        avlTreeNode* temp = node;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        return temp;
    }

    avlTreeNode* AVLInsert(avlTreeNode* r, avlTreeNode* newNode) {
        if (r == NULL) {
            r = newNode;
            return r;
        }

        if (newNode->value < r->value) {
            r->left = AVLInsert(r->left, newNode);
        }
        else if (newNode->value > r->value) {
            r->right = AVLInsert(r->right, newNode);
        }
        else {
            r->count += 1;
            return r;
        }

        int balanceFactor = getBalanceFactor(r);

        //left-left case (must do zag-zag)
        if (balanceFactor > 1 && newNode->value < r->left->value)
            return rightRotate(r);

        //right-right case (must do zig-zig)
        if (balanceFactor < -1 && newNode->value > r->right->value)
            return leftRotate(r);

        //right-left case (must do zig-zag)
        if (balanceFactor < -1 && newNode->value < r->right->value) {
            r->right = rightRotate(r->right);
            return leftRotate(r);
        }

        //left-right case (must do zag-zig)
        if (balanceFactor > 1 && newNode->value > r->left->value) {
            r->left = leftRotate(r->left);
            return rightRotate(r);
        }

        AVLinsertOperations++;
        AVLTreeCreationOperations++;
        return r;
    }

    avlTreeNode* searchNode(avlTreeNode* r, int val) {
        //Increment search operations by one
        AVLsearchOperations += 1;
        if (r == NULL || r->value == val) {
            return r;
        }

        else if (val < r->value) {
            //Move left if value is smaller
            return searchNode(r->left, val);
            
        }

        else {
            //Move right if value is bigger
            return searchNode(r->right, val);
            
        }

    }

    avlTreeNode* deleteNode(avlTreeNode* r, int v) {
        
        //Increment delete operations by one
        AVLdeleteOperations += 1;
        //Base case 
        if (r == NULL) {
            return NULL;
        }
        //Move left if value is smaller
        else if (v < r->value) {
            r->left = deleteNode(r->left, v);
        }
        //Move right if value is bigger
        else if (v > r->value) {
            r->right = deleteNode(r->right, v);
        }
        else {

            if (r->left == NULL && r->right == NULL) {
                delete r;
                return NULL; 
            }
            else if (r->left == NULL) {
                avlTreeNode* temp = r->right;
                delete r;
                return temp; 
            }
            else if (r->right == NULL) {
                avlTreeNode* temp = r->left;
                delete r;
                return temp; 
            }
            else {
                avlTreeNode* temp = lowestNode(r->right);
                r->value = temp->value;
                r->right = deleteNode(r->right, temp->value);
            }
        }
        return r; //Return the updated root
    }

};



int main() {
    //Initialize arrays for the tree and count
    int arr[max_rows][max_coloumns] = { {0} };
    int countArr[max_rows][max_coloumns] = { {0} };
    int input;
    string operationsInput;


    //Open the insert/input file
    //Make sure to put this same file into the avlInputFile below
    ifstream inputFile("test.txt");


    //Check if the file opens fine
    if (!inputFile) {
        cerr << "Error opening the file." << endl;
        return 1;
    }
    //Check if the file is empty
    else if (inputFile.peek() == ifstream::traits_type::eof()) {
        cerr << "Your file is empty.";
        outputFile << "Put inserts in this file and try again.";
        return 1;
    }

    //Read values from the file and insert them into the tree
    while (inputFile >> input) {
        string check = to_string(input);
        if (input != stoi(check)) {
            input = 0;
        }
        cout << "Insert: " << input << endl;
        cout << "Tree: " << endl;
        outputFile << "Insert: " << input << endl;
        outputFile << "Tree: " << endl;
        insertNode(arr, countArr, max_coloumns / 2, input, 0, 18);
        for (int i = 0; i < max_rows; ++i) {
            for (int j = 0; j < max_coloumns; ++j) {
                if (arr[i][j] == 0) {
                    cout << " ";
                    outputFile << " ";
                }
                else if (countArr[i][j] == 1) {
                    cout << arr[i][j];
                    outputFile << arr[i][j];
                }
                else {
                    cout << arr[i][j] << "-" << countArr[i][j];
                    outputFile << arr[i][j] << "-" << countArr[i][j];
                }
            }
            cout << endl;
            outputFile << endl;
        }

        //Find the lowest row with a non-zero element and print the tree height
        int height = heightFind(arr);
        if (height != -1) {
            cout << "Tree Height: " << height << endl;
            outputFile << "Tree Height: " << height << endl;
            cout << endl;
        }
        else {
            cout << "Tree Height: 0" << endl;
            outputFile << "Tree Height: 0" << endl;
            cout << endl;
        }
    }


    ifstream operationsFile("testOp.txt");



    //Check if the file opens fine
    if (!operationsFile) {
        cerr << "Error opening the operations file." << endl;
        outputFile << "Error opening the operations file." << endl;
    }
    //Check if the file is empty
    else if (operationsFile.peek() == ifstream::traits_type::eof()) {
        cerr << "Your operation file is empty." << endl;
        outputFile << "Put operations in this file and try again." << endl;
    }

    while (operationsFile >> operationsInput) {
        int height = heightFind(arr);
        if (operationsInput == "D") {
            string operationNumber;
            if (height == -1) {
                cout << "Tree is empty, no delete operations can be performed" << endl;
                outputFile << "Tree is empty, no delete operations can be performed" << endl;
            }
            else if (operationsFile >> operationNumber) {
                int operationValue = stoi(operationNumber);
                deleteNode(arr, countArr, max_coloumns / 2, operationValue, 0, 18);
                cout << "Delete: " << operationValue << endl;
                outputFile << "Delete: " << operationValue << endl;
                cout << "Node " << operationValue << " deleted successfully in " << deleteOperations << " operations." << endl;
                outputFile << "Node " << operationValue << " deleted successfully in " << deleteOperations << " operations." << endl;
                totalDeleteOperations += deleteOperations;
                deleteOperations = 0;
            }
            else {
                cerr << "Error, missing input after delete operation." << endl;
                outputFile << "Error missing input after delete operation." << endl;
            }
        }
        else if (operationsInput == "S") {
            string operationNumber;
            cout << "Operation: " << operationsInput << endl;
            if (height == -1) {
                cout << "Tree is empty, no search operations can be performed." << endl;
                outputFile << "Tree is empty, no search operations can be performed." << endl;
            }
            else if (operationsFile >> operationNumber) {
                int operationValue = stoi(operationNumber);
                cout << "Search: " << operationValue << endl;
                outputFile << "Search: " << operationValue << endl;

                if (searchNode(arr, countArr, max_coloumns / 2, operationValue, 0, 18)) {
                    searchOperations += 1;
                    cout << "Found " << operationNumber << " in " << searchOperations << " operations." << endl;
                    outputFile << "Found " << operationNumber << " in " << searchOperations << " operations." << endl;
                    totalSearchOperations += searchOperations;
                    searchOperations = 0;
                }
                else {
                    cout << "Not found: " << endl;
                    outputFile << "Not found: " << endl;
                }
            }
            else {
                cerr << "Error, missing input after search operation." << endl;
                outputFile << "Error missing input after search operation." << endl;
            }
        }
        else if (operationsInput == "I") {
            string operationNumber;
            if (operationsFile >> operationNumber) {
                insertOperations = 0;
                int operationValue = stoi(operationNumber);
                cout << "Insert Value: " << operationValue << endl;
                outputFile << "Insert Value: " << operationValue << endl;
                insertNode(arr, countArr, max_coloumns / 2, operationValue, 0, 18);
                cout << insertOperations << " operations" << endl;
                outputFile << insertOperations << " operations" << endl;
                totalInsertOperations += insertOperations;
                insertOperations = 0;
            }
            else {
                cout << "Invalid, Please Fix" << endl;
                outputFile << "Invalid, Please Fix" << endl;
            }
        }
        else {
            cout << "Invalid operation: " << operationsInput << ". Skipping to the next input." << endl;
            outputFile << "Invalid operation: " << operationsInput << ". Skipping to the next input." << endl;
            // Consume the remaining input line
            string temp;
            getline(operationsFile, temp);
        }
        for (int i = 0; i < max_rows; ++i) {
            for (int j = 0; j < max_coloumns; ++j) {
                if (arr[i][j] == 0) {
                    cout << " ";
                    outputFile << " ";
                }
                else if (countArr[i][j] == 1) {
                    cout << arr[i][j];
                    outputFile << arr[i][j];
                }
                else {
                    cout << arr[i][j] << "-" << countArr[i][j];
                    outputFile << arr[i][j] << "-" << countArr[i][j];
                }
            }
            cout << endl;
            outputFile << endl;
        }

        //Find the lowest row with a non-zero element and print the tree height
        if (height != -1) {
            cout << "Tree Height: " << height << endl;
            outputFile << "Tree Height: " << height << endl;
            cout << endl;
        }
        else {
            cout << "Tree Height: 0" << endl;
            outputFile << "Tree Height: 0" << endl;
            cout << endl;
        }
    }

    int totalOperations = creationOperations + totalSearchOperations + totalInsertOperations + totalDeleteOperations;

    cout << "Creation: " << creationOperations << endl;
    outputFile << "Creation: " << creationOperations << endl;

    cout << "Search: " << totalSearchOperations << endl;
    outputFile << "Search: " << totalSearchOperations << endl;

    cout << "Insert: " << totalInsertOperations << endl;
    outputFile << "Insert: " << totalInsertOperations << endl;

    cout << "Delete: " << totalDeleteOperations << endl;
    outputFile << "Delete: " << totalDeleteOperations << endl;

    cout << "Total: " << totalOperations << endl;
    outputFile << "Total: " << totalOperations << endl;

    inputFile.close();
    operationsFile.close();

    AVLTree avlTree;
    avlTreeNode* newNode = new avlTreeNode();

    // Open the file
    //Same file as original input file
    ifstream avlFile("test.txt");

    if (!avlFile) {
        cerr << "Error opening file." << endl;
        outputFile << "Error opening file." << endl;
        return 1;
    }

    int val;

    //Read values from the file and insert them into the AVL tree
    //Handling of inserts
    while (avlFile >> val) {
        avlTreeNode* newNode = new avlTreeNode(val);

        avlTree.root = avlTree.AVLInsert(avlTree.root, newNode);
        cout << endl;
        outputFile << endl;

    }


    cout << "AVL Tree: " << endl;
    outputFile << "AVL Tree: " << endl;

    cout << "Root: " << avlTree.root->value << endl;
    outputFile << "Root: " << avlTree.root->value << endl;

    cout << "Root is on the left to better show balanced AVL Tree." << endl;
    outputFile << "Root is on the left to better show balanced AVL Tree." << endl;

    cout << "Upper half is the 'right' subtree and lower half is the 'left' subtree in the AVL tree." << endl;
    outputFile << "Upper half is the 'right' subtree and lower half is the 'left' subtree in the AVL tree." << endl;

    avlTree.printAVLTree(avlTree.root, 6);
    cout << endl;
    outputFile << endl;

    cout << "AVL Tree Height: " << avlTree.AVLHeight(avlTree.root) << endl;
    outputFile << "AVL Tree Height: " << avlTree.AVLHeight(avlTree.root) << endl;

    cout << "AVL Tree Creation Operations: " << AVLTreeCreationOperations << endl;
    outputFile << "AVL Tree Creation Operations: " << AVLTreeCreationOperations << endl;

    cout << endl;
    outputFile << endl;

    ifstream avlOpFile("testOp.txt");

    if (!avlOpFile) {
        cerr << "Error opening operations file." << endl;
        outputFile << "Error opening operations file." << endl;
        return 1;
    }
    //Check if the file is empty
    else if (avlOpFile.peek() == ifstream::traits_type::eof()) {
        cerr << "Your operation file is empty." << endl;
        outputFile << "Put operations in this file and try again." << endl;
    }

    string operationsAVLInput;

    while (avlOpFile >> operationsAVLInput) {
        int height = avlTree.AVLHeight(avlTree.root);
        if (operationsAVLInput == "I") {
            string operationAVLNumber;
            if (avlOpFile >> operationAVLNumber) {
                AVLinsertOperations = 2;
                int operationAVLNumbers = stoi(operationAVLNumber);
                avlTreeNode* newNode = new avlTreeNode(operationAVLNumbers);

                avlTree.root = avlTree.AVLInsert(avlTree.root, newNode);
                cout << endl;
                outputFile << endl;

                cout << operationAVLNumber << " inserted in " << AVLinsertOperations << " operations." << endl;
                outputFile << operationAVLNumber << " inserted in " << AVLinsertOperations << " operations." << endl;

                totalAVLinsertOperations += AVLinsertOperations;

                cout << "AVL Tree: " << endl;
                outputFile << "AVL Tree: " << endl;

                cout << "Root: " << avlTree.root->value << endl;
                outputFile << "Root: " << avlTree.root->value << endl;


                avlTree.printAVLTree(avlTree.root, 6);
                cout << endl;
                outputFile << endl;

                cout << "AVL Tree Height: " << avlTree.AVLHeight(avlTree.root) << endl;
                outputFile << "AVL Tree Height: " << avlTree.AVLHeight(avlTree.root) << endl;


                cout << endl;
                outputFile << endl;
            }
            else {
                cout << "Invalid, Please Fix" << endl;
                outputFile << "Invalid, Please Fix" << endl;
            }
        }
        else if (operationsAVLInput == "D") {
            string operationAVLNumber;

            if (height == -1) {
                cout << "Tree is empty, no delete operations can be performed" << endl;
                outputFile << "Tree is empty, no delete operations can be performed" << endl;
            }
            else if (avlOpFile >> operationAVLNumber) {
                int operationValue = stoi(operationAVLNumber);
                avlTreeNode* newNode = avlTree.searchNode(avlTree.root, operationValue);
                AVLdeleteOperations += AVLsearchOperations;
                AVLsearchOperations = 0;
                if (newNode != NULL) {
                    if (newNode->count > 0) {
                        newNode->count -= 1;
                        cout << operationAVLNumber << " was deleted in " << AVLdeleteOperations << " operations." << endl;
                        outputFile << operationAVLNumber << " was deleted in " << AVLdeleteOperations << " operations." << endl;
                        totalAVLdeleteOperations += AVLdeleteOperations;
                        AVLdeleteOperations = 0;
                    }
                    else {
                        avlTree.root = avlTree.deleteNode(avlTree.root, operationValue);
                        cout << operationAVLNumber << " was deleted in " << AVLdeleteOperations << " operations." << endl;
                        outputFile << operationAVLNumber << " was deleted in " << AVLdeleteOperations << " operations." << endl;
                        totalAVLdeleteOperations += AVLdeleteOperations;
                        AVLdeleteOperations = 0;
                    }

                }
                else {
                    cout << "Atempted node to delete does not exist." << endl;
                    outputFile << "Atempted node to delete does not exist." << endl;
                }
            }
            if (avlTree.root != NULL) {
            cout << "AVL Tree: " << endl;
            outputFile << "AVL Tree: " << endl;

            cout << "Root: " << avlTree.root->value << endl;
            outputFile << "Root: " << avlTree.root->value << endl;

            cout << "Root is on the left to better show balanced AVL Tree." << endl;
            outputFile << "Root is on the left to better show balanced AVL Tree." << endl;


            
                avlTree.printAVLTree(avlTree.root, 6);
                cout << endl;
                outputFile << endl;


                cout << "AVL Tree Height: " << avlTree.AVLHeight(avlTree.root) << endl;
                outputFile << "AVL Tree Height: " << avlTree.AVLHeight(avlTree.root) << endl;


                cout << endl;
                outputFile << endl;
            }
        }
        else if (operationsAVLInput == "S") {
            string operationAVLNumber;
            cout << "Operation: " << operationsAVLInput << endl;
            if (avlOpFile >> operationAVLNumber) {
                int operationAVLNumbers = stoi(operationAVLNumber);
                avlTreeNode* newNode = new avlTreeNode(operationAVLNumbers);
                avlTree.searchNode(avlTree.root, operationAVLNumbers);
                if (newNode != NULL) {
                    cout << operationAVLNumber << " found in " << AVLsearchOperations << " operations." << endl;
                    outputFile << operationAVLNumber << " found in " << AVLsearchOperations << " operations." << endl;
                    totalAVLsearchOperations += AVLsearchOperations;
                    AVLsearchOperations = 1;
                }
                else {
                    cout << "Value NOT found" << endl;
                }


                cout << "AVL Tree: " << endl;
                outputFile << "AVL Tree: " << endl;

                cout << "Root: " << avlTree.root->value << endl;
                outputFile << "Root: " << avlTree.root->value << endl;

                cout << "Root is on the left to better show balanced AVL Tree." << endl;
                outputFile << "Root is on the left to better show balanced AVL Tree." << endl;

                avlTree.printAVLTree(avlTree.root, 6);
                cout << endl;
                outputFile << endl;

                cout << "AVL Tree Height: " << avlTree.AVLHeight(avlTree.root) << endl;
                outputFile << "AVL Tree Height: " << avlTree.AVLHeight(avlTree.root) << endl;


                cout << endl;
                outputFile << endl;
                
            }
            else {
                cerr << "Error, missing input after search operation." << endl;
                outputFile << "Error missing input after search operation." << endl;
            }
        }
    }

    int totalAVLOperations = AVLTreeCreationOperations + totalAVLsearchOperations + totalAVLinsertOperations + totalAVLdeleteOperations;

    cout << "Creation: " << AVLTreeCreationOperations << endl;
    outputFile << "Creation: " << AVLTreeCreationOperations << endl;

    cout << "Search: " << totalAVLsearchOperations << endl;
    outputFile << "Search: " << totalAVLsearchOperations << endl;

    cout << "Insert: " << totalAVLinsertOperations << endl;
    outputFile << "Insert: " << totalAVLinsertOperations << endl;

    cout << "Delete: " << totalAVLdeleteOperations << endl;
    outputFile << "Delete: " << totalAVLdeleteOperations << endl;

    cout << "Total: " << totalAVLOperations << endl;
    outputFile << "Total: " << totalAVLOperations << endl;



    avlFile.close();
    avlOpFile.close();
    outputFile.close();

    return 0;
}
