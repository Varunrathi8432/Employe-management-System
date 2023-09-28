#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

class Employee
{
private:
    int empid;
    char name[30];
    double salary;

public:
    void input()
    {
        cout << "\nEnter employee id, name and salary : ";
        cin >> empid;
        cin.ignore();
        cin.getline(name, 30);
        cin >> salary;
    }
    void display()
    {
        cout << endl;
        cout << empid << " ";
        cout << name << "  ";
        cout << salary << endl;
    }
    void store();
    void printAll();
    void search(int id);
    void edit(int id);
    void del(int id);
};
void Employee::store()
{
    ofstream fout;
    fout.open("EmployeeFile", ios::binary | ios::app);
    fout.write((char *)this, sizeof(*this));
    fout.close();
    cout << "Employee record saved." << endl;
}
void Employee::printAll()
{
    ifstream fin;
    fin.open("EmployeeFile", ios::binary | ios::in);
    bool found = false;
    if (!fin)
    {
        cout << "File Not Found or unable to find"<<endl;
        return;
    }
    fin.read((char *)this, sizeof(*this));
    while (!fin.eof())
    {
        display();
        fin.read((char *)this, sizeof(*this));
        found = true;
    }
    if (!found)
    {
        cout << "File is empty. please insert data " << endl;
    }

    fin.close();
}
void Employee::edit(int id)
{
    Employee e;
    ifstream fin;
    ofstream fout;
    fin.open("EmployeeFile", ios::binary | ios::in);
    if (!fin)
    {
        cout << "File Not Found";
        return;
    }
    fout.open("tempfile", ios::binary | ios::out);
    fin.read((char *)&e, sizeof(e));
    bool found = false;
    while (!fin.eof())
    {
        if (id == e.empid)
        {
            cout << "Enter correct Employee name: ";
            cin.ignore();
            cin.getline(e.name, 30);
            cout << "Enter correct Employee salary: ";
            cin >> e.salary;
            found = true;
        }
        fout.write((char *)&e, sizeof(e));
        fin.read((char *)&e, sizeof(e));
    }
    fin.close();
    fout.close();
    if (!found)
    {
        cout << "Employee with ID " << id << " not found." << endl;
        remove("tempfile");
    }
    else
    {
        remove("EmployeeFile");
        rename("tempfile", "EmployeeFile");
        cout << "Employee with ID " << id << " has been updated." << endl;
    }
}

void Employee::search(int id)
{
    ifstream fin;
    bool Found = false;
    fin.open("EmployeeFile", ios::binary | ios::in);
    if (!fin)
        cout << "File Not Found";
    else
    {
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            if (empid == id)
            {
                display();
                Found = true;
                break;
            }
            fin.read((char *)this, sizeof(*this));
        }
        if (!Found)
            cout << "Search Failed, record not found" << endl;
    }
    fin.close();
}

void Employee::del(int id)
{
    Employee e;
    ifstream fin;
    ofstream fout;
    bool found = false;

    fin.open("EmployeeFile", ios::binary | ios::in);
    if (!fin)
    {
        cout << "File Not Found";
        return;
    }

    fout.open("tempfile", ios::binary | ios::out);
    fin.read((char *)&e, sizeof(e));

    while (!fin.eof())
    {
        if (id != e.empid)
        {
            fout.write((char *)&e, sizeof(e));
        }
        else
        {
            found = true;
        }
        fin.read((char *)&e, sizeof(e));
    }

    fin.close();
    fout.close();

    if (!found)
    {
        cout << "Employee with ID " << id << " not found." << endl;
        remove("tempfile");
    }
    else
    {
        remove("EmployeeFile");
        rename("tempfile", "EmployeeFile");
        cout << "Employee with ID " << id << " has been deleted." << endl;
    }
}

int menu()
{
    int choice;
    cout << "\n1. New Record";
    cout << "\n2. Edit Record";
    cout << "\n3. View All Records";
    cout << "\n4. Search a Record";
    cout << "\n5. Delete a Record";
    cout << "\n6. Exit";
    cout << "\n\nEnter your choice : ";
    cin >> choice;
    return choice;
}
int main()
{
    Employee emp;
    int id;
    while (true)
    {
        switch (menu())
        {
        case 1:
            emp.input();
            emp.store();
            break;
        case 2:
            cout << "Enter employee id to edit : ";
            cin >> id;
            emp.edit(id);
            break;
        case 3:
            emp.printAll();
            break;
        case 4:
            cout << "Enter employee id to search : ";
            cin >> id;
            emp.search(id);
            break;
        case 5:
            cout << "Enter employee id to delete : ";
            cin >> id;
            emp.del(id);
            break;
        case 6:
            exit(0);
        default:
            cout << "\nInvalid Choice"<<endl;
        }
    }
    cout << endl;
    return 0;
}