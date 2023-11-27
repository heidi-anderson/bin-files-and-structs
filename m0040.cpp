#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void printFile(fstream& records);
bool applyBonus(fstream& records, int id);

struct empData /* given struct of employee data */
{
    int id;
    char firstName[20];
    char lasName[40];
    double salary;
    double bonus;
};

int main(int argc, char** argv)
{
    fstream records; /* binary file with all the records */

    if (argc != 3) /* checking for correct usage */
    {
        cout << "Usage: m0040.exe binaryData employeeID" << endl;
        return 0;
    }

    records.open(argv[1], ios::in | ios::out | ios::ate | ios::binary); /* open the file */

    if (!records.is_open()) /* checking to see if the file opened */
    {
        cout << "Unable to open binary file: " << argv[1] << endl;
        return 0;
    }

    printFile(records);
    cout << endl;
    int id = stoi(argv[2]);
    if (applyBonus(records, id))
    {
        cout << "Employee ID " << id << " has been updated." << endl << endl;
        printFile(records);
    }
    else
    {
        cout << "Employee ID " << id << " was not found." << endl << endl;
        printFile(records);
    }

    records.close();
    return 0;
}

void printFile(fstream& records)
{
    empData emp; /* instance of empData struct */

    records.clear(); /* reset flags */
    records.seekg(0, ios::beg); /* put pointer at beginning */

    while (records.read((char*)&emp, sizeof(empData))) /* read until eof */
    {
        cout << std::fixed << std::setprecision(2); /* display 2 decimal places */
        cout << setw(7) << emp.id << " "
            << left << setw(20) << emp.firstName
            << setw(40) << emp.lasName << right
            << " Salary: " << setw(10) << emp.salary
            << " Bonus: " << setw(10) << emp.bonus << endl;
    }
}

bool applyBonus(fstream& records, int id)
{
    empData emp;
    streamoff position;

    records.clear(); /* reset flags */
    records.seekg(0, ios::beg); /* put pointer at beginning */

    while (records.read((char*)&emp, sizeof(empData))) /* read the record */
    {
        
    
        if (emp.id == id) /* add the bonus to the employee w the correct id */
        {
            emp.bonus += 500;

            position = records.tellp(); /* get current position of ptr */
            records.seekp(position - sizeof(empData)); /* move pointer to correct spot */
            records.write((char*)&emp, sizeof(empData)); /* write out data */

            return true;
        }

    }

    return false;
}
