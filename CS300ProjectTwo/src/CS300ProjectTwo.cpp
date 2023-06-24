//============================================================================
// Name        : CS300ProjectTwo.cpp
// Author      : Joshua James
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>


// Course structure
struct Course {
    std::string courseNumber;
    std::string courseTitle;
    std::vector<std::string> prerequisites;
};

// Function to load data from CSV file into data structure
void loadDataStructure(std::vector<Course>& courses) {
    std::string fileName = "ABCUCourses.csv";  //CSV file name

    std::ifstream inputFile(fileName);
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            std::string token;
            Course course;

            // Read course number
            std::getline(iss, token, ',');
            course.courseNumber = token;

            // Read course title
            std::getline(iss, token, ',');
            course.courseTitle = token;

            // Read prerequisites
            while (std::getline(iss, token, ',')) {
                course.prerequisites.push_back(token);
            }

            // Add the course to the data structure
            courses.push_back(course);
        }
        inputFile.close();
        std::cout << "Data loaded successfully!" << std::endl;
    } else {
        std::cout << "Error opening file: " << fileName << std::endl;
    }
}

void printCourseList(const std::vector<Course>& courses) {
	std::cout << "Here is a sample schedule:" << std::endl;
    std::vector<Course> sortedCourses = courses;
    std::sort(sortedCourses.begin(), sortedCourses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
    });

    for (const Course& course : sortedCourses) {
        std::cout << course.courseNumber << ", " << course.courseTitle << std::endl;
    }
}

void printCourseInformation(const std::vector<Course>& courses, const std::string& courseNumber) {
    for (const Course& course : courses) {
        if (course.courseNumber == courseNumber) {
            std::cout << course.courseNumber << ", " << course.courseTitle << std::endl;
            std::cout << "Prerequisites: ";
            if (course.prerequisites.empty()) {
                std::cout << "None";
            } else {
                for (size_t i = 0; i < course.prerequisites.size(); i++) {
                    std::cout << course.prerequisites[i];
                    if (i != course.prerequisites.size() - 1) {
                        std::cout << ", ";
                    }
                }
            }
            std::cout << std::endl;
            return;
        }
    }

    std::cout << "Course not found!" << std::endl;
}


int main() {
    std::vector<Course> courses;

    // Load the data structure from the CSV file
    loadDataStructure(courses);

    int choice = 0;
    while (choice != 4) {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Load Data Structure" << std::endl;
        std::cout << "2. Print Course List" << std::endl;
        std::cout << "3. Print Course Information" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                loadDataStructure(courses); //reload data structure from the CSV file
                break;
            case 2:
                printCourseList(courses); //Print a sorted list of the courses
                break;
            case 3: {
                std::string courseCode;
                std::cout << "What course do you want to know about? ";
                std::cin.ignore(); // Ignore any remaining newline characters from previous input
                std::getline(std::cin, courseCode);

                bool courseFound = false;
                for (const Course& course : courses) {
                    if (course.courseNumber == courseCode) {
                        std::cout << course.courseNumber << ", " << course.courseTitle << std::endl;
                        std::cout << "Prerequisites: ";
                        if (course.prerequisites.empty()) {
                            std::cout << "None";
                        } else {
                            for (size_t i = 0; i < course.prerequisites.size(); i++) {
                                std::cout << course.prerequisites[i];
                                if (i != course.prerequisites.size() - 1) {
                                    std::cout << ", ";
                                }
                            }
                        }
                        std::cout << std::endl;
                        courseFound = true;
                        break;
                    }
                }

                if (!courseFound) {
                    std::cout << "Course not found!" << std::endl;
                }
                break;
            }

            case 4:
                std::cout << "Thank you for using the course planner!" << std::endl;
                break;
            default:
                std::cout << "is not a valid option" << std::endl;
        }
    }

    return 0;
}
