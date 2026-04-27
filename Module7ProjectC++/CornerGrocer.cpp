//Keenan Vargas
//04/18/2026
//SNHU CS 210 Programming Languages - Project 3
#include <iostream>
//includes fstream so it can read from files and write to those files (for frequency.dat in this case)
#include <fstream>
//includes map for storing and managing the item names and the amount of times they appear
#include <map>
#include <string>
#include <iomanip>

using namespace std;

class SearchItem{

    //private variables
    private:
        map<string, int> itemCounter;

        //public methods because they need access
        public:
        //method that loads data from the frequency.dat file
        void loadData(const string& filename){
            ifstream inputFile(filename.c_str());
            string item;

            //if the file does not open correctly then it will print out this error
            //this is to prevent the program from reading or accessing a file that has not been opened correctly
            if (!inputFile) {
                cout << "Error: Could not open input file.\n";
                return;
            }

            //uses a map to count how many times each item appears in the whole list
            while (inputFile >> item) {
                itemCounter[item]++;
            }

            inputFile.close();
        }
        //method that gets the number of times the item appears
        int getItemCounter(const string& item){
            if (itemCounter.find(item) != itemCounter.end()) {
                return itemCounter[item];
            }
            return 0;
        }
        //method that prints the item counter
        void printAllCounters(){
            cout << "\nItem Counter List:\n";
            for (map<string, int>::iterator it = itemCounter.begin(); it != itemCounter.end(); ++it) {
        cout << it->first << " " << it->second << endl;
            }
        }
        //a method that prints the histogram (a visual graph with '*' instead of a bar)
        void printHistogram(){
            cout << "\nItem Histogram:\n";
            for (map<string, int>::iterator it = itemCounter.begin(); it != itemCounter.end(); ++it) {
                cout << it->first << " ";
                //adds * for each time the item appears
                for (int i = 0; i < it->second; i++) {
                    cout << "*";
                }
                cout << endl;
            }
        }  
        //method that saves the number of times the item appears in the list all in
        //a file so that they can be stored and reused
        void writeBackupFile(const string& filename){
            ofstream outFile(filename.c_str());

            //checks to see if the file opened
            if (!outFile) {
                cout << "Error: Could not create backup file.\n";
                return;
            }

            for (map<string, int>::iterator it = itemCounter.begin(); it != itemCounter.end(); ++it) {
                outFile << it->first << " " << it->second << endl;
            }

            //closes the file to save the data properly
            outFile.close();
        }

};
//main method where all the methods are called to
int main(){
    //initializes a variable called search for calling the methods from before
    SearchItem search;

    //load data in this line using the files location/path
    search.loadData("CS210_Project_Three_Input_File.txt");
    //write the backup file here too for storing all the times the item appears
    search.writeBackupFile("frequency.dat");

    int choice;
    string item;
    cout<< "Welcome to Corner Grocer! " << endl;

    do{
        //display options for the user (with 1-4) and choice as input
        cout << "\n===== Corner Grocer Menu =====\n";
        cout << "1. Search for item frequency\n";
        cout << "2. Print all item frequencies\n";
        cout << "3. Print histogram\n";
        cout << "4. Exit\n";
        //prompts the user to input their choice
        cout << "Enter choice: ";
        cin >> choice;

        //Exception Handling for when there is an invalid input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number 1-4.\n";
            continue;
        }
        //use switches for every option the user could choose (the cases reflect the user choice)
        switch (choice) {
            //case 1 for when the user just wants to find how many times the item appears in the list
        case 1:
            cout << "Enter item name: ";
            cin >> item;
            cout << item << " appears "
                 << search.getItemCounter(item)
                 << " times.\n";
            break;

        //case 2 prints the amount of times it appears in the whole list for each item
        case 2:
            search.printAllCounters();
            break;
        
        //case 3 prints the histogram for the items (visual representation so like '*' type of graph)
        case 3:
            search.printHistogram();
            break;

        //case 4 just exits out the app
        case 4:
            cout << "Exiting program...\n";
            break;

        //when the user input for choice is not any of the numbers (1-4)
        default:
            cout << "Invalid option. Try again.\n";
        }
    }
    //repeats while the user does not exit the program
    while(choice != 4);

    return 0;
}