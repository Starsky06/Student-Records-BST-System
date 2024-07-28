#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include    "Student.h"

using namespace std;
//function prototype
bool readFile(const char *, BST *);
int menu();

// read file function
bool readFile(const char* filename, BST* t1) {
	ifstream inFile(filename);

	string line;
	Student stu;
	int count = 0;
	if (!inFile.is_open()) {
		cout << "File cannot be opened!!!" << endl;
		return false;
	}
	//read the file
	while (!inFile.eof()) {

		inFile >> line >> line >> line >> stu.id;
		inFile >> line >> line;
		inFile.getline(stu.name, 30);
		inFile.ignore();
		inFile >> line >> line;
		inFile.getline(stu.address, 100);
		inFile.ignore();
		inFile >> line >> line;
		inFile.getline(stu.DOB, 20);
		inFile.ignore();
		inFile >> line >> line >> line;
		inFile.getline(stu.phone_no, 10);
		inFile.ignore();
		inFile >> line >> line;
		inFile.getline(stu.course, 5);
		inFile.ignore();
		inFile >> line >> line;
		inFile >> stu.cgpa;
		inFile.ignore();

		t1->insert(stu);
		count++;


	}
	
	cout << "The number of student records successfully read: " << count << endl;
	cout << endl;
	return true;
}
// menu display
int menu()
{
	int choice;

	cout << "**************************MAIN MENU*************************" << endl;
	cout << "*(1) Read data to BST                                      *" << endl;
	cout << "*(2) Print deepest nodes                                   *" << endl;
	cout << "*(3) Display student                                       *" << endl;
	cout << "*(4) Clone Subtree                                         *" << endl;
	cout << "*(5) Print Level Nodes                                     *" << endl;
	cout << "*(6) Print Path                                            *" << endl;
	cout << "*(7) Exit                                                  *" << endl;
	cout << "************************************************************" << endl;

	cout << "============================================================" << endl;
	cout << "Kindly enter your choice (1 - 7) : ";
	cin >> choice;

	if (choice < 1 || choice > 7) {

		cout << "Invalid Input ! Please Try Again !" << endl;
		return 0;
	}
	system("cls");

	return choice;
}



int main() {

	int choice;
	bool exit = false;

	const char* filename = "student.txt";
	int order,source;
	BST t1;


	do {
		
		//display menu 
		choice = menu();

		switch (choice)
		{
		case 1:

			
			if (readFile(filename, &t1))
			{
				cout << "Successfully read and record the student list !!!" << endl;
				cout << endl;
			}
			else
			{
				cout << "Unable to read and record the student list !!! " << endl;
				cout << endl;
			}
			break;

		case 2:
			// find deepest nodes
			cout << "The deepest nodes of tree is/are : ";
			
			t1.deepestNodes();
			cout << endl;
			break;

		case 3:
			// display student information according asc and desc order
			cout << "Press 1 for ascending order | | Press 2 for descending order" << endl;
			cout << endl;
			cout << "Enter your choice: ";
			cin >> order;
			cout << endl;
			system("cls");

			if (order == 1) {
				
				cout << "You have selected " << order << " for ascending order." << endl;

			}
				
			else if (order == 2) {
				
				cout << "You have selected " << order << " for ascending order." << endl;

			}
				
			else {
				cout << "Wrong input ! PLEASE TRY AGAIN !" << endl;
				break;
			}

			cout << "-----------------------------------------------------------------------------------------------" << endl;
			cout << "Press 1 for print to screen | | Press 2 for print to a file name student_info.txt" << endl;
			cout << endl;
			cout << "Enter your choice: ";
			cin >> source;

			if (source == 1) {
				cout << endl;
				cout << "You have selected " << source << " for print to screen." << endl;

			}
				
			else if (source == 2) {
				cout << endl;
				cout << "You have selected " << source << " for print to a file name student_info.txt." << endl;

			}
				
			else {
				cout << "Wrong input ! PLEASE TRY AGAIN !" << endl;
				break;
			}
			cout << endl;
			cout << endl;
			
			if(source == 1)
				cout << "The student's information list below : " << endl;

			
			t1.display(order, source);
			cout << endl;
			cout << "-----------------------------------------------------------------------------------------------" << endl;
			cout << "Display or Insert successfully !!! " << endl;

			if (source == 2) {
				cout << endl;
				cout << "Go to the student_info.txt file to check it !  " << endl;
			}
			cout << endl;
			break;

		case 4:
			// clone tree
			if (!t1.empty()) {
				string id;
				type item; 
				cout << "Which student do you want to clone to another tree ? " << endl;
				cout << endl;
				cout << "Enter the student's ID (NUMBER) : ";
				cin >> item.id;
				

				BST t2;

				if (t2.cloneSubtree(t1, item)) {
					cout << "Subtree cloned successfully !" << endl;
					cout << endl;
				}
				else {
					cout << endl;
					cout << "Failed to clone subtree !" << endl;
					cout << endl;
				}
			}
			else {
				cout << "The tree is empty. Cannot clone subtree." << endl;
				cout << endl;
			}
			break;

		case 5:
			// print level by level 
			cout << "The level of output show below : " << endl;
			cout << endl;
			t1.printLevelNodes();
			cout << endl;
			break;

		case 6:

			// print the external path
			t1.printPath();
			cout << endl;

			break;

		case 7:
			// exit
			cout << "Exiting...................................................................." << endl;
			cout << endl;
			exit = true;
			break;
		}

		if (!exit) {
			
			system("PAUSE");
			system("cls");
		}

	} while (!exit);

	return 0;
	
}







