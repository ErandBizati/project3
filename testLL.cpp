/**
 * file testLL.cpp
 * author Erand Bizati
 * date 21 October 2023
 *
 * brief test file for DblLink.h
 *
 * details this file contains testing methods to be used for my doubly linked list project
 */
#include <iostream>
#include "DblLink.h"                                                    // include the header file

using namespace std;

                                                                        // func implementations
void insertItem(DblLink<int>& list);
void removeItem(DblLink<int>& list);
void printForwards(DblLink<int>& list);
void printBackwards(DblLink<int>& list);

int main() {
    DblLink<int> list;                                                  // declare doubly linked list of integers
    int choice;                                                         // store users menu choice

                                                                        // main menu loop
    while (true) {
        cout << "\nUser Menu" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Remove" << endl;
        cout << "3. Print forwards" << endl;
        cout << "4. Print backwards" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;                                                  // read user choice

                                                                        // input validation
        if (cin.fail()) {
            cin.clear();                                                // clear the error flag
            cin.ignore(10000, '\n');                                    // ignore any remaining input in the stream
            cout << "Invalid input. Please enter an integer." << endl;
            continue;                                                   // skip the rest of the loop and start from the beginning
        }

                                                                        // menu switch case
        switch (choice) {
            case 1:                                                     // insert an item into the list
                insertItem(list);
                break;
            case 2:                                                     // remove an item from the list
                if (!list.isEmpty()) {
                    removeItem(list);
                } else {
                    cout << "List is empty, cannot remove." << endl;
                }
                break;
            case 3:                                                     // print the list forwards
                if (!list.isEmpty()) {
                    printForwards(list);
                } else {
                    cout << "List is empty." << endl;
                }
                break;
            case 4:                                                     // print the list backwards
                if (!list.isEmpty()) {
                    printBackwards(list);
                } else {
                    cout << "List is empty." << endl;
                }
                break;
            case 5:                                                     // exit the program
                cout << "Exiting... Goodbye!" << endl;
                return 0;
            default:                                                    // invalid menu choice
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

                                                                        // function to insert an item into the list
void insertItem(DblLink<int>& list) {
    int item;
    cout << "Enter item to insert: ";
    cin >> item;
    list.insert(item);
    cout << "Item inserted." << endl;
}

                                                                        // function to remove an item from the list
void removeItem(DblLink<int>& list) {
    int item;
    cout << "Enter item to remove: ";
    cin >> item;
    if (list.remove(item)) {
        cout << "Item removed." << endl;
    } else {
        cout << "Item not found. Cannot remove." << endl;
    }
}

                                                                        // function to print the list forwards
void printForwards(DblLink<int>& list) {
    DblLinkItr<int> itr = list.begin();                                 // get an iterator pointing to the beginning of the list
    cout << "List (Forwards): ";
    while (!itr.isEmpty()) {
        cout << *itr << " ";                                            // print the current item
        ++itr;                                                          // move to the next item
    }
    cout << endl;
}

                                                                        // function to print the list backwards
void printBackwards(DblLink<int>& list) {
    DblLinkItr<int> itr = list.end();                                   // get an iterator pointing to the end of the list
    cout << "List (Backwards): ";
    while (!itr.isEmpty()) {
        cout << *itr << " ";                                            // print the current item
        --itr;                                                          // move to the previous item
    }
    cout << endl;
}