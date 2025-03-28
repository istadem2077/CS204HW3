#include <iostream>
#include <fstream>
#include <string>
#include "TabsDLL.h"
using namespace std;

int main() {
    // Create a tabs manager using doubly linked list
    TabsDLL tabs;
    string filename;

    // Get input file name from user
    cout << "Please enter the file name:" << endl;
    cin >> filename;

    // Try to open the specified file
    ifstream file(filename);

    // Check if file opened successfully
    if (file.fail())
    {
        cout << "The file couldn't be opened." << endl;
        cout << "Program aborted." << endl;
    }
    else
    {
        string command;
        do
        {
            file >> command;
            // For "open" command: creates a new tab or adds a page to existing tab
            if (command == "open")
            {
                int tab_id;
                string page;
                file >> tab_id >> page;  // Read tab ID and page URL
                cout << "COMMAND: open " << tab_id << " " << page << endl;
                string openedPage;
                // Check if tab already exists
                if (tabs.tabExists(tab_id) == true)
                {
                    // Update existing tab with new page
                    openedPage = tabs.update(tab_id, page);
                    cout << "Updated tab " << tab_id << " with page: " << openedPage << endl;
                    cout << endl;
                }
                else
                {
                    // Create a new tab with the specified page
                    openedPage = tabs.newTab(tab_id, page);
                    cout << "Created new tab " << tab_id << " with page: " << openedPage << endl;
                    cout << endl;
                }
            }
            // For "back" command: navigate to previous page in specified tab
            else if (command == "back")
            {
                int tab_id;
                file >> tab_id;  // Read tab ID
                cout << "COMMAND: back " << tab_id << endl;
                tabs.backTab(tab_id);  // Pop the top page from tab's stack
                cout << endl;
            }
            // Fo "close" command: close the specified tab and remove all its pages
            else if (command == "close")
            {
                int tab_id;
                file >> tab_id;  // Read tab ID
                cout << "COMMAND: close " << tab_id << endl;
                tabs.closeTab(tab_id);  // Remove the tab and free memory
                cout << endl;
            }
            // For "display" command: show all tabs and their page counts
            else if (command == "display")
            {
                cout << "COMMAND: display" << endl;
                tabs.display();  // Display all tabs in both forward and backward directions
                cout << endl;
            }
            // For "quit" command: close all tabs and exit
            else if (command == "quit")
            {
                cout << "COMMAND: quit" << endl;
                tabs.quitAndDisplay();  // Close all tabs and display closing messages
                cout << endl;
            }
        } while (command != "quit"); // Process commands until "quit" is encountered
    }
    cout << "Program Finished. Bye Bye" << endl;
    return 0;
}