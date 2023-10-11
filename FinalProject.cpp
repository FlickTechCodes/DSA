/*  Randall Flick
    Project 2
    CS300
    10/15/2023
    */

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

// FIXME: Consider adding a destructor to clean up dynamically allocated memory

// Struct to represent individual courses
struct Course {
    std::string courseNumber;  // Holds the course number
    std::string title;  // Holds the course title
    std::vector<std::string> prerequisites;  // Holds the prerequisites

    // Constructor to initialize a Course object with course number, title, and prerequisites
    Course(std::string cn, std::string t, std::vector<std::string> p)
        : courseNumber(cn), title(t), prerequisites(p) {}
};

// Struct to represent nodes in the binary search tree, each holding a Course object
struct Node {
    Course course;  // Holds the course data
    Node* left;  // Pointer to the left child node
    Node* right;  // Pointer to the right child node

    // Constructor to initialize a Node with a Course object
    Node(Course c) : course(c), left(nullptr), right(nullptr) {}
};

// Class to represent the binary search tree for storing and managing Course objects
class BST {
private:
    Node* root;  // Root of the BST

    // Inserts a new course into the BST
    Node* insert(Node* node, Course course) {
        // If node is null, create a new node with the course
        if (node == nullptr) {
            return new Node(course);
        }

        // Compare course numbers to decide the position of the new course in the BST
        if (course.courseNumber < node->course.courseNumber) {
            node->left = insert(node->left, course);  // Insert in the left subtree
        } else if (course.courseNumber > node->course.courseNumber) {
            node->right = insert(node->right, course);  // Insert in the right subtree
        }

        return node;  // Return the node pointer
    }

    // Performs in-order traversal and prints the BST
    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);  // Traverse the left subtree
            // Print the course number and title
            std::cout << node->course.courseNumber << ": " << node->course.title << std::endl;
            inOrder(node->right);  // Traverse the right subtree
        }
    }

    // Searches for a course in the BST by course number
    Node* searchNode(Node* node, std::string courseNumber) {
        if (node == nullptr || node->course.courseNumber == courseNumber) {
            return node;  // Return the node if found or null
        }

        // Recur on the left or right subtree based on the course number
        if (courseNumber < node->course.courseNumber) {
            return searchNode(node->left, courseNumber);
        }
        return searchNode(node->right, courseNumber);
    }

public:
    // Constructor to initialize an empty BST
    BST() : root(nullptr) {}

    // Inserts a new course into the BST
    void insert(Course course) {
        root = insert(root, course);
    }

    // Prints the courses in the BST in order
    void printInOrder() {
        inOrder(root);
    }

    // Searches for a course by course number and returns the course data
    Course search(std::string courseNumber) {
        Node* node = searchNode(root, courseNumber);
        if (node != nullptr) {
            return node->course;
        } else {
            return Course("", "", {});  // Return an empty course if not found
        }
    }
};

// Main function to drive the program
int main() {
    BST bst;  // Create a BST object
    // TODO: Prompt the user for the file name instead of hardcoding it
    std::string filename = "courses.txt";  // FIXME: The filename is hardcoded

    std::ifstream file(filename);  // Open the file
    if (!file) {  // Check if the file opened successfully
        std::cerr << "Unable to open file " << filename << std::endl;
        return 1;  // Return an error code if file opening failed
    }

    std::string line, courseNumber, title, prerequisite;
    while (std::getline(file, line)) {  // Read the file line by line
        std::stringstream ss(line);
        // Parse the course data from each line
        std::getline(ss, courseNumber, ',');
        std::getline(ss, title, ',');
        std::vector<std::string> prerequisites;
        while (std::getline(ss, prerequisite, ',')) {  // Parse prerequisites if available
            prerequisites.push_back(prerequisite);
        }
        bst.insert(Course(courseNumber, title, prerequisites));  // Insert the course into the BST
    }

    int choice = 0;
    do {
        // Print the menu options
        std::cout << "\nMenu:\n"
                  << "1. Load Data Structure\n"
                  << "2. Print Course List\n"
                  << "3. Print Course\n"
                  << "4. Exit\n"
                  << "Enter choice: ";

        std::cin >> choice;  // Read the user's choice

        // Process the user's choice
        switch (choice) {
            case 1:
                // FIXME: Implement the functionality to reload the data structure
                std::cout << "Data Loaded.\n";
                break;
            case 2:
                bst.printInOrder();  // Print the course list in order
                break;
            case 3: {
                std::cout << "Enter course number: ";
                std::cin >> courseNumber;  // Read the course number from the user

                Course course = bst.search(courseNumber);  // Search for the course
                if (!course.courseNumber.empty()) {  // Print the course details if found
                    std::cout << "Course Title: " << course.title << "\nPrerequisites: ";
                    for (const auto& pre : course.prerequisites) {
                        std::cout << pre << " ";
                    }
                    std::cout << std::endl;
                } else {
                    std::cout << "Course not found.\n";  // Print an error message if not found
                }
                break;
            }
            case 4:
                std::cout << "Exiting...\n";  // Exit the program
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";  // Handle invalid choices
        }
    } while (choice != 4);  // Continue until the user chooses to exit

    return 0;  // End of program
}

