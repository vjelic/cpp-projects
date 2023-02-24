//*****************************************************************************************************
//
//		This program reads employee data from a file, stores it in an array of structures, and allows
//      users to add more employees. The code displays the current list of employees after each
//      update, using standard input and file input/output. The program opens the file "Employees.txt"
//      and reads the number of employees, calling the readEmployees function to store the data in an
//      array of structures. The displayEmployees function shows the employee information. The user
//      can add new employees by inputting the information through the inputEmployees function. The
//      process can be repeated until the user stops, and the combined list is displayed each time. If
//      the file can't be opened, an error message is displayed and memory is deallocated at the end
//      of the program.
//
//*****************************************************************************************************

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

//*****************************************************************************************************
struct dateEmployed {
    int month,
        day,
        year;
};
struct Employee {
    string name;
    int age;
    dateEmployed date;
};

Employee *readEmployees(const string &empFile, int &numEmps);
void displayEmployees(const Employee emps[], int numEmps);
Employee *inputEmployees(Employee *emps, int &numEmps);

//*****************************************************************************************************

int main() {
    string empFile = "Employees.txt";
    int numEmps;
    fstream f;
    char entry;

    f.open(empFile, ios::in);
    while (f.is_open()) {
        f >> numEmps;
        f.close();

        Employee *emps = readEmployees(empFile, numEmps);
        displayEmployees(emps, numEmps);

        cout << "\nAny additional employees need to be added? (Y/N)" << endl;
        cin >> entry;
        if (entry == 'y' || entry == 'Y') {
            Employee *newEmps = inputEmployees(emps, numEmps);
            displayEmployees(newEmps, numEmps);

            delete[] emps;
            emps = nullptr;
            delete[] newEmps;
            newEmps = nullptr;
        } else {
            delete[] emps;
            emps = nullptr;

            break;
        }
    }
    if (!f)
        cerr << "Error: Unable to open file" << endl;     // cerr is unbuffered and best for error handling

    return 0;
}

//*****************************************************************************************************

Employee *readEmployees(const string &empFile, int &numEmps) {
    fstream f;

    f.open(empFile, ios::in);
    Employee *tmp = new Employee[numEmps];     // dynamically allocate array of structures to store employee data
    f.ignore(2);                               // ignore first two characters of file (number of employees and newline)

    for (int i = 0; i < numEmps; ++i) {
        getline(f, tmp[i].name, ',');
        f >> tmp[i].age;
        f.ignore();
        f >> tmp[i].date.month;
        f.ignore();
        f >> tmp[i].date.day;
        f.ignore();
        f >> tmp[i].date.year;
        f.ignore();
    }
    f.close();

    return tmp;
}

//*****************************************************************************************************

Employee *inputEmployees(Employee *emps, int &numEmps) {
    fstream f;
    int newEntries,
        oldEmps = numEmps,     // store number of employees before adding new ones
        age,
        month,
        day,
        year;
    string name;

    cout << "\nHow many?" << endl;
    cin >> newEntries;

    cin.ignore();                                               // ignore newline character so getline() works properly
    Employee *newemps = new Employee[numEmps + newEntries];     // numEmps + newEntries = total number of employees

    for (int i = 0; i < numEmps; i++) {
        newemps[i].name = emps[i].name;
        newemps[i].age = emps[i].age;
        newemps[i].date.month = emps[i].date.month;
        newemps[i].date.day = emps[i].date.day;
        newemps[i].date.year = emps[i].date.year;
    }

    numEmps = numEmps + newEntries;     // update number of employees to pass by reference to main()

    f.open("Employees.txt", ios::out);     // open file for writing ( ios::out is for writing)
    f << numEmps << endl;

    for (int i = 0; i < numEmps - newEntries; ++i)
        f << newemps[i].name << "," << newemps[i].age << ","
          << newemps[i].date.month << "/" << newemps[i].date.day
          << "/" << newemps[i].date.year << endl;
    f.close();

    f.open("Employees.txt", ios::app);     // open file for appending ( ios::app is for appending)

    for (int i = oldEmps; i < numEmps; ++i) {
        cout << "\nName: ";
        getline(cin, name);

        cout << "Age: ";
        cin >> age;

        cout << "\nDate Employed \n"
             << "Month: ";
        cin >> month;

        cout << "Day: ";
        cin >> day;

        cout << "Year: ";
        cin >> year;

        cin.ignore();
        newemps[i].name = name;
        newemps[i].age = age;
        newemps[i].date.month = month;
        newemps[i].date.day = day;
        newemps[i].date.year = year;
        f << newemps[i].name << "," << newemps[i].age << ","
          << newemps[i].date.month << "/" << newemps[i].date.day
          << "/" << newemps[i].date.year << endl;
    }
    f.close();

    return newemps;     // return pointer to new array of structures
}

//*****************************************************************************************************

void displayEmployees(const Employee emps[], int numEmps) {
    cout << "\n";
    cout << left     // Set the text alignment to left for all columns
         << setw(30)
         << "Name"     // width for the "NAME" column is 30 characters
         << setw(20)
         << "Age"     // width for the "AGE" column is 20 characters
         << setw(10)
         << "Date Employed" << endl;     // width for the "DATE EMPLOYED" column is 20 characters

    cout << setfill('-') << setw(63) << "" << endl;     // line of 70 dashes to separate the header from the data
    cout << setfill(' ');                               // reset the fill character to a space for the data

    for (int i = 0; i < numEmps; ++i)
        cout << left
             << setw(30) << emps[i].name
             << setw(23) << emps[i].age
             << right << setw(10)     // right align the date for better formatting
             << setw(2) << emps[i].date.month << "/"
             << setw(2) << emps[i].date.day << "/"
             << setw(4) << emps[i].date.year << endl;
}

//*****************************************************************************************************

/*

Name                          Age                 Date Employed
---------------------------------------------------------------
Stephen Smith                 25                     12/15/2001
Susan Kim-Jones               33                      1/ 9/2012
Praew Chaem Choi              52                      8/22/1999

Any additional employees need to be added? (Y/N)
N

*****************************************************************************************************

Name                          Age                 Date Employed
---------------------------------------------------------------
Stephen Smith                 25                     12/15/2001
Susan Kim-Jones               33                      1/ 9/2012
Praew Chaem Choi              52                      8/22/1999

Any additional employees need to be added? (Y/N)
Y

How many?
3

Name: Nicholas Ragland
Age: 31

Date Employed
Month: 7
Day: 8
Year: 1991

Name: Olivia Davisson
Age: 24

Date Employed
Month: 2
Day: 27
Year: 1999

Name: Bob Bobbers
Age: 55

Date Employed
Month: 1
Day: 1
Year: 2023

Name                          Age                 Date Employed
---------------------------------------------------------------
Stephen Smith                 25                     12/15/2001
Susan Kim-Jones               33                      1/ 9/2012
Praew Chaem Choi              52                      8/22/1999
Nicholas Ragland              31                      7/ 8/1991
Olivia Davisson               24                      2/27/1999
Bob Bobbers                   55                      1/ 1/2023


*/