#include <iostream>
#include <string>

using namespace std;

class Contact
{
private:
    string name;
    string email;
    string address;
    string phoneNumber;
public:
    Contact() {}

    Contact(const Contact & c)
    {
        name = c.name;
        email = c.email;
        address = c.address;
        phoneNumber = c.phoneNumber;
    }

    Contact(string n, string e, string adr, string pN)
        : name(n), email(e), address(adr), phoneNumber(pN) {}
   
    //OPERATOR Over Loading to compare email IDs     

    bool operator >(const Contact & c)
    {
        return email.compare(c.email) > 0;
    }

    bool operator <(const Contact & c)
    {
        return email.compare(c.email) < 0;
    }

    bool operator ==(const Contact & c)
    {
        return email.compare(c.email) == 0;
    }

    void setName(string n) { name = n;}
    void setEmail(string e) { email = e;}
    void setAddress(string a) { address = a;}
    void setPhoneNumber(string p) { phoneNumber = p;}

    string getName() { return name;}
    string getEmail() { return email;}
    string getAddress() { return address;}
    string getPhoneNumber() { return phoneNumber;}

    void printContact()
    {
        cout << endl << "---------------------" << endl;
        cout << "Name: " << getName() << endl;
        cout << "Phone #: " << getPhoneNumber() << endl;
        cout << "Email: " << getEmail() << endl;
        cout << "Address: " << getAddress() << endl;
        cout << endl << "---------------------" << endl;
    }
};