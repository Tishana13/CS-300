#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm> // For std::transform

using namespace std;

// Structure to hold course information
struct Course {
    string courseNumber; // The course number (e.g., CS101)
    string title;        // The title of the course (e.g., Introduction to Programming)
    vector<string> prerequisites; // List of prerequisite courses
};

// Global map to hold courses, with course number as the key
unordered_map<string, Course> courses;

// Function to load course data from a CSV file
static void loadData() {
    string filename = "CS 300 ABCU_Advising_Program_Input.csv"; // Path to your CSV file
    ifstream file(filename); // Open the file for reading

    // Check if the file was successfully opened
    if (!file.is_open()) {
        cout << "Error: Could not open file '" << filename << "'.\n";
        return; // Exit the function if file cannot be opened
    }

    string line;
    // Read each line of the file
    while (getline(file, line)) {
        istringstream stream(line); // Create a string stream from the line
        Course course; // Create a Course object to store data

        // Read course number from the line
        getline(stream, course.courseNumber, ',');
        // Convert course number to upper case to ensure consistency
        std::transform(course.courseNumber.begin(), course.courseNumber.end(), course.courseNumber.begin(), ::toupper);

        // Read course title from the line
        getline(stream, course.title, ',');

        string prereq;
        // Read all prerequisites from the line
        while (getline(stream, prereq, ',')) {
            course.prerequisites.push_back(prereq); // Add each prerequisite to the course
        }

        // Check for duplicate course entries
        if (courses.find(course.courseNumber) != courses.end()) {
            cout << "Warning: Course " << course.courseNumber << " already exists. Skipping duplicate entry.\n";
        }
        else {
            courses[course.courseNumber] = course; // Add course to the map
        }
    }
    file.close(); // Close the file after reading
    cout << "Data loaded successfully from '" << filename << "'.\n";
}

// Function to print the list of courses
static void printCourseList() {
    cout << "Here is a sample schedule:\n";
    // Iterate through the courses map and print course details
    for (const auto& pair : courses) {
        cout << pair.second.courseNumber << ", " << pair.second.title << endl; // Print course number and title
    }
}

// Function to print details of a specific course
static void printCourse() {
    cout << "What course do you want to know about? ";
    string inputCourse;
    cin >> inputCourse; // Get course number input from the user

    // Convert input to upper case for consistency
    std::transform(inputCourse.begin(), inputCourse.end(), inputCourse.begin(), ::toupper);

    // Check if the course exists in the map
    if (courses.find(inputCourse) != courses.end()) {
        cout << courses[inputCourse].courseNumber << ", " << courses[inputCourse].title << endl; // Print course details
        if (!courses[inputCourse].prerequisites.empty()) {
            cout << "Prerequisites: ";
            // Print each prerequisite for the course
            for (const auto& prereq : courses[inputCourse].prerequisites) {
                cout << prereq << " ";
            }
            cout << endl;
        }
        else {
            cout << "No prerequisites.\n"; // Indicate if there are no prerequisites
        }
    }
    else {
        cout << "Course not found.\n"; // Indicate if the course does not exist
    }
}

int main() {
    int choice; // Variable to store user's menu choice
    do {
        // Display the menu
        cout << "Welcome to the course planner.\n";
        cout << "1. Load Data Structure.\n";
        cout << "2. Print Course List.\n";
        cout << "3. Print Course.\n";
        cout << "9. Exit\n";
        cout << "What would you like to do? ";
        cin >> choice; // Get user's choice

        // Process the user's choice using a switch statement
        switch (choice) {
        case 1:
            loadData(); // Load course data from CSV
            break;
        case 2:
            printCourseList(); // Print the list of courses
            break;
        case 3:
            printCourse(); // Print details of a specific course
            break;
        case 9:
            cout << "Thank you for using the course planner.\n"; // Exit message
            break;
        default:
            cout << choice << " is not a valid option.\n"; // Handle invalid choice
            break;
        }
    } while (choice != 9); // Continue until the user chooses to exit

    return 0; // Indicate successful completion
}
