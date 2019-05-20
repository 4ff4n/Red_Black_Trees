#include <iostream>
#include <string>

#include "rbtree.h"

using namespace std;

class Manager
{
public:
    Tree tree;

    void addContact();
    void deleteContact();
    void findContact();
    void printContacts();
};

void Manager::addContact()
{
    Contact c;

    string name, email, phone, address;

    cin.ignore();
    cout << "Enter Name:"; getline(cin, name);
    cout << "Enter Email:"; getline(cin, email);
    cout << "Enter Phone Number:"; getline(cin, phone);
    cout << "Enter Address:"; getline(cin, address);

    c.setName(name);
    c.setEmail(email);
    c.setPhoneNumber(phone);
    c.setAddress(address);

    if (! tree.addItem(c)) {
        cout << endl << "----------------------" << endl;
        cout << endl << "Record with this email already exists." << endl;
        cout << endl << "----------------------" << endl;
    } else {
        cout << endl << "----------------------" << endl;
        cout << endl << "Record is added to the tree." << endl;
        cout << endl << "----------------------" << endl;
    } 
}

void Manager::deleteContact()
{
    string email;
    Contact c;

    cin.ignore();
    cout << "Enter email for the record:"; getline(cin, email);

    c.setEmail(email);

    if (! tree.deleteItem(c)) {
        cout << endl << "----------------------" << endl;
        cout << endl << "Record not found!" << endl;
        cout << endl << "----------------------" << endl;
    } else {
        cout << endl << "----------------------" << endl;
        cout << endl << "Record is deleted!" << endl;
        cout << endl << "----------------------" << endl;
    }
}

void Manager::findContact()
{
    string email;
    Contact c;
    TreeNode *tn;

    cin.ignore();
    cout << "Enter email for the record:"; getline(cin, email);

    c.setEmail(email);

    tn = tree.findItem(c);

    if (tn == nullptr) {
        cout << endl << "----------------------" << endl;
        cout << endl << "Record not found!" << endl;
        cout << endl << "----------------------" << endl;
    } else {
        cout << endl << "----------------------" << endl;
        cout << endl << "Record Details" << endl;
        cout << endl << "----------------------" << endl;
        tn->item.printContact();
    }
}

void Manager::printContacts()
{
    if (tree.isEmpty()) {
        cout << endl << "----------------------" << endl;
        cout << endl << "The tree is empty." << endl;
        cout << endl << "----------------------" << endl;
    } else {
        cout << endl << "------All Records-----" << endl;
        tree.printTree();
        cout << endl << "----------End---------" << endl;
    }
}

int main()
{
    Manager m;

    int choice = 0;

    while(true) {
        cout << "1) Add a record." << endl;
        cout << "2) Delete a record." << endl;
        cout << "3) Find a record." << endl;
        cout << "4) Show all the records." << endl;
        cout << "5) Exit." << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                m.addContact();
                break;
            case 2:
                m.deleteContact();
                break;
            case 3:
                m.findContact();
                break;
            case 4:
                m.printContacts();
                break;
            case 5:
                exit(0);
            default:
                continue;
            }
    }
}