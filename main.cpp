#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Contact {
protected:
    string firstName, lastName, email, address;
    string phoneNumber;
    string category;

public:
    friend istream& operator>>(istream& is, Contact& contact) {
        cout << "Enter your first name: ";
        is >> contact.firstName;
        cout << "Enter your last name: ";
        is >> contact.lastName;
        cout << "Enter phone number: ";
        is >> contact.phoneNumber;
        cout << "Enter address: ";
        is.ignore();
        getline(is, contact.address);
        cout << "Enter email: ";
        is >> contact.email;
        cout << "Enter category (Friend/Family/Others): ";
        is >> contact.category;
        return is;
    }

    friend ostream& operator<<(ostream& os, const Contact& contact) {
        os << "Name: " << contact.firstName << " " << contact.lastName << endl;
        os << "Phone: " << contact.phoneNumber << endl;
        os << "Address: " << contact.address << endl;
        os << "Email: " << contact.email << endl;
        os << "Category: " << contact.category << endl;
        return os;
    }
};

class Phonebook : public Contact {
public:
    void createContact() {
        char ch;
        ofstream f1;
        f1.open("Phonebook.txt", ios::binary | ios::app);

        cin >> *this;
        f1.write(reinterpret_cast<char*>(this), sizeof(*this));

        cout << "Contact has been successfully created..." << endl;
        f1.close();
    }

    void showContact() {
        ifstream f2;
        f2.open("Phonebook.txt", ios::binary);

        cout << "\n================================" << endl;
        cout << "LIST OF CONTACTS" << endl;
        cout << "================================" << endl;

        while (f2.read(reinterpret_cast<char*>(this), sizeof(*this))) {
            cout << *this;
            cout << "================================" << endl;
        }
        f2.close();
    }

    void searchByPhnNo() {
        ifstream f3;
        string phone;
        cout << "Enter phone number: ";
        cin >> phone;
        f3.open("Phonebook.txt", ios::binary);

        while (f3.read(reinterpret_cast<char*>(this), sizeof(*this))) {
            if (phone == phoneNumber) {
                cout << *this;
                f3.close();
                return;
            }
        }
        cout << "\nNo record found." << endl;
        f3.close();
    }

    void searchByfName() {
        ifstream f4;
        string fName;
        cout << "Enter first name: ";
        cin >> fName;
        f4.open("Phonebook.txt", ios::binary);

        while (f4.read(reinterpret_cast<char*>(this), sizeof(*this))) {
            if (fName == firstName) {
                cout << *this;
                f4.close();
                return;
            }
        }
        cout << "\nNo record found." << endl;
        f4.close();
    }

    void deleteByfName() {
        string fName;
        int flag = 0;
        ofstream f6;
        ifstream f5;

        f5.open("Phonebook.txt", ios::binary);
        f6.open("temp.txt", ios::binary);

        cout << "Enter first name to delete contact: ";
        cin >> fName;

        while (f5.read(reinterpret_cast<char*>(this), sizeof(*this))) {
            if (firstName != fName) {
                f6.write(reinterpret_cast<char*>(this), sizeof(*this));
            } else {
                flag = 1;
            }
        }
        f5.close();
        f6.close();
        remove("Phonebook.txt");
        rename("temp.txt", "Phonebook.txt");

        if (flag == 1) {
            cout << "\nContact Deleted..." << endl;
        } else {
            cout << "\nContact Not Found..." << endl;
        }
    }

    void deleteByPhnNO() {
        string num;
        int flag = 0;
        ofstream f7;
        ifstream f8;

        f8.open("Phonebook.txt", ios::binary);
        f7.open("temp.txt", ios::binary);

        cout << "Enter phone number to delete contact: ";
        cin >> num;

        while (f8.read(reinterpret_cast<char*>(this), sizeof(*this))) {
            if (phoneNumber != num) {
                f7.write(reinterpret_cast<char*>(this), sizeof(*this));
            } else {
                flag = 1;
            }
        }
        f8.close();
        f7.close();
        remove("Phonebook.txt");
        rename("temp.txt", "Phonebook.txt");

        if (flag == 1) {
            cout << "\nContact Deleted..." << endl;
        } else {
            cout << "\nContact Not Found..." << endl;
        }
    }

    void deleteAllContacts() {
        char confirm;
        cout << "Are you sure you want to delete all contacts? (Y/N): ";
        cin >> confirm;

        if (confirm == 'Y' || confirm == 'y') {
            ofstream f9;
            f9.open("Phonebook.txt", ios::binary | ios::trunc);
            f9.close();
            cout << "All contacts have been deleted successfully." << endl;
        } else {
            cout << "Deletion operation canceled." << endl;
        }
    }

    void editContact() {
        string num;
        fstream f9;

        cout << "Edit contact" << endl;
        cout << "===============================" << endl << endl;
        cout << "Enter the phone number to be edited: ";
        cin >> num;

        f9.open("Phonebook.txt", ios::binary | ios::out | ios::in);

        while (f9.read(reinterpret_cast<char*>(this), sizeof(*this))) {
            if (phoneNumber == num) {
                cout << "Enter new record" << endl;
                cin >> *this;
                int pos = -1 * sizeof(*this);
                f9.seekp(pos, ios::cur);
                f9.write(reinterpret_cast<char*>(this), sizeof(*this));
                cout << "\nContact Successfully Updated..." << endl;
                f9.close();
                return;
            }
        }
        cout << "\nNo record found." << endl;
        f9.close();
    }

    void printByCategory() {
        ifstream f10;
        string chosenCategory;
        cout << "Enter category (Friend/Family/Others): ";
        cin >> chosenCategory;
        f10.open("Phonebook.txt", ios::binary);

        cout << "\n================================" << endl;
        cout << "LIST OF CONTACTS (Category: " << chosenCategory << ")" << endl;
        cout << "================================" << endl;

        vector<Contact> contacts;

        while (f10.read(reinterpret_cast<char*>(this), sizeof(*this))) {
            if (chosenCategory == category) {
                contacts.push_back(*this);
            }
        }
        f10.close();

        if (!contacts.empty()) {
            for (Contact& contact : contacts) {
                cout << contact;
                cout << "================================" << endl;
            }
        } else {
            cout << "No contacts found in the chosen category." << endl;
        }
    }
};

int main() {

    cout << "\n\n\n\n\n\n\n\n\t\t\t * WELCOME TO CONTACT MANAGEMENT SYSTEM *";

    while (1) {
        Phonebook c1;
        int choice;

        cout << "\nCONTACT MANAGEMENT SYSTEM" << endl;
        cout << "\nMAIN MENU" << endl;
        cout << "=====================" << endl;
        cout << "[1] Add a new Contact" << endl;
        cout << "[2] List all Contacts" << endl;
        cout << "[3] Search for a Contact By Phone Number" << endl;
        cout << "[4] Search for a Contact By First Name" << endl;
        cout << "[5] Delete a Contact By Phone Number" << endl;
        cout << "[6] Delete a Contact By First Name" << endl;
        cout << "[7] Delete all Contacts" << endl;
        cout << "[8] Edit a Contact" << endl;
        cout << "[9] Print Contacts by Category" << endl;
        cout << "[0] Exit" << endl;
        cout << "=====================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                c1.createContact();
                break;

            case 2:
                c1.showContact();
                break;

            case 3:
                c1.searchByPhnNo();
                break;

            case 4:
                c1.searchByfName();
                break;

            case 5:
                c1.deleteByPhnNO();
                break;

            case 6:
                c1.deleteByfName();
                break;

            case 7:
                c1.deleteAllContacts();
                break;

            case 8:
                c1.editContact();
                break;

            case 9:
                c1.printByCategory();
                break;

            case 0:
                cout << "\n\n\n\t\t\tThank you for using CMS." << endl << endl;
                exit(0);
                break;

            default:
                continue;
        }

        int opt;
        cout << "\n\n::Enter Your Choice :\n[1] Main Menu\t\t[0] Exit\n";
        cin >> opt;

        switch (opt) {
            case 0:
                
                cout << "\n\n\n\t\t\tThank you for using Phonebook." << endl << endl;
                exit(0);
                break;

            default:
                continue;
        }
    }

    return 0;
}
