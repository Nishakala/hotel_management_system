/*
	
	Title			: Hotel Management System
	Language		: C++
	Author			: Nisha Kala
*/
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

class hotel {
private:
    int room_no;
    char name[30];
    char address[50];
    char phone[15];
    int days;
    float fare;

public:
    void main_menu();
    void add();
    void display();
    void rooms();
    void edit();
    int check(int);
    void modify(int);
    void delete_rec(int);
};

void intro() {
    cout << "\n\n";
    cout << "==============================================================\n";
    cout << "   Welcome to the C++ Hotel Management System\n";
    cout << "   Developed by: Nisha Kala\n";
    cout << "==============================================================\n\n";
}

void head() {
    cout << "==============================================================\n";
    cout << "   XYZ Group of Hotels\n";
    cout << "   Hotel Management System\n";
    cout << "==============================================================\n\n";
}

void hotel::main_menu() {
    int choice;
    while (choice != 5) {
        head();
        cout << "\n\t\t\t\t*************";
        cout << "\n\t\t\t\t* MAIN MENU *";
        cout << "\n\t\t\t\t*************";
        cout << "\n\n\n\t\t\t1. Book A Room";
        cout << "\n\t\t\t2. Customer Record";
        cout << "\n\t\t\t3. Rooms Allotted";
        cout << "\n\t\t\t4. Edit Record";
        cout << "\n\t\t\t5. Exit";
        cout << "\n\n\t\t\tEnter Your Choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            add();
            break;
        case 2:
            display();
            break;
        case 3:
            rooms();
            break;
        case 4:
            edit();
            break;
        case 5:
            exit(0);
        default:
            cout << "\n\n\t\t\tWrong choice.....!!!";
            cout << "\n\t\t\tPress any key to continue....!!";
            cin.ignore();
            cin.get();
        }
    }
}

void hotel::add() {
    head();
    int r, flag;
    ofstream fout("Record.dat", ios::app | ios::binary);
    cout << "\n Enter Customer Details";
    cout << "\n ----------------------";
    cout << "\n\n Room no: ";
    cin >> r;
    flag = check(r);
    if (flag)
        cout << "\n Sorry..!!! Room is already booked";
    else {
        room_no = r;
        cout << " Name: ";
        cin.ignore(); // Ignore the newline character left in the buffer
        cin.getline(name, 30);
        cout << " Address: ";
        cin.getline(address, 50);
        cout << " Phone No: ";
        cin.getline(phone, 15);
        cout << " No of Days to Checkout: ";
        cin >> days;
        fare = days * 900;
        fout.write(reinterpret_cast<char*>(this), sizeof(hotel));
        cout << "\n Room is booked...!!!";
    }

    cout << "\n Press any key to continue.....!!";
    cin.ignore();
    cin.get();
    fout.close();
}

void hotel::display() {
    head();
    ifstream fin("Record.dat", ios::in | ios::binary);
    int r, flag;
    cout << "\n Enter room no: ";
    cin >> r;
    while (!fin.eof()) {
        fin.read(reinterpret_cast<char*>(this), sizeof(hotel));
        if (room_no == r) {
            head();
            cout << "\n Customer Details";
            cout << "\n ----------------";
            cout << "\n\n Room no: " << room_no;
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone no: " << phone;
            cout << "\n Days: " << days;
            cout << "\n Total Fare: " << fare;
            flag = 1;
        }
    }
    if (flag == 0)
        cout << "\n Sorry Room no. not found or vacant....!!";
    cout << "\n\n Press any key to continue....!!";
    cin.ignore();
    cin.get();
    fin.close();
}

void hotel::rooms() {
    head();
    ifstream fin("Record.dat", ios::in | ios::binary);
    cout << "\n\t\t\t    List Of Rooms Allotted";
    cout << "\n\t\t\t    ----------------------";
    while (!fin.eof()) {
        fin.read(reinterpret_cast<char*>(this), sizeof(hotel));
        cout << "\n Room no: " << room_no << "\n Name: " << name;
        cout << "\n Address: " << address << "\n Phone: " << phone;
        cout << "\n Days: " << days << "\n Total: " << fare;
        cout << "\n**********************************";
    }
    cout << "\n\n\n\t\t\tPress any key to continue.....!!";
    cin.ignore();
    cin.get();
    fin.close();
}

void hotel::edit() {
    head();
    int choice, r;
    cout << "\n EDIT MENU";
    cout << "\n ---------";
    cout << "\n\n 1. Modify Customer Record";
    cout << "\n 2. Delete Customer Record";
    cout << "\n Enter your choice: ";
    cin >> choice;

    head();
    cout << "\n Enter room no: ";
    cin >> r;
    switch (choice) {
    case 1:
        modify(r);
        break;
    case 2:
        delete_rec(r);
        break;
    default:
        cout << "\n Wrong Choice.....!!";
    }
    cout << "\n Press any key to continue....!!!";
    cin.ignore();
    cin.get();
}

int hotel::check(int r) {
    int flag = 0;
    ifstream fin("Record.dat", ios::in | ios::binary);
    while (!fin.eof()) {
        fin.read(reinterpret_cast<char*>(this), sizeof(hotel));
        if (room_no == r) {
            flag = 1;
            break;
        }
    }
    fin.close();
    return flag;
}

void hotel::modify(int r) {
    head();
    long pos;
    int flag = 0;
    fstream file("Record.dat", ios::in | ios::out | ios::binary);
    while (!file.eof()) {
        pos = file.tellg();
        file.read(reinterpret_cast<char*>(this), sizeof(hotel));
        if (room_no == r) {
            cout << "\n Enter New Details";
            cout << "\n -----------------";
            cout << "\n Name: ";
            cin.ignore();
            cin.getline(name, 30);
            cout << " Address: ";
            cin.getline(address, 50);
            cout << " Phone no: ";
            cin.getline(phone, 15);
            cout << " Days: ";
            cin >> days;
            fare = days * 900;
            file.seekg(pos);
            file.write(reinterpret_cast<char*>(this), sizeof(hotel));
            cout << "\n Record is modified....!!";
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        cout << "\n Sorry Room no. not found or vacant...!!";
    file.close();
}

void hotel::delete_rec(int r) {
    head();
    int flag = 0;
    char ch;
    ifstream fin("Record.dat", ios::in | ios::binary);
    ofstream fout("temp.dat", ios::out | ios::binary);
    while (!fin.eof()) {
        fin.read(reinterpret_cast<char*>(this), sizeof(hotel));
        if (room_no == r) {
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone No: " << phone;
            cout << "\n Days: " << days;
            cout << "\n Total Fare: " << fare;
            cout << "\n\n Do you want to delete this record (y/n): ";
            cin >> ch;
            if (ch == 'n')
                fout.write(reinterpret_cast<char*>(this), sizeof(hotel));
            flag = 1;
            break;
        } else
            fout.write(reinterpret_cast<char*>(this), sizeof(hotel));
    }
    fin.close();
    fout.close();
    if (flag == 0)
        cout << "\n Sorry room no. not found or vacant...!!";
    else {
        remove("Record.dat");
        rename("temp.dat", "Record.dat");
    }
}

int main() {
    hotel h;
    cout << "\n\n\n";
    intro();
    cout << "\n\n\n\t\t\tPress any key to continue....!!";
    cin.ignore();
    cin.get();
    head();
    char id[5], pass[7];
    cout << "\n\n\t\t\t\tusername => ";
    cin >> id;
    cout << "\n\t\t\t\tpassword => ";
    cin >> pass;
    cout << "\n\n\t";
    if (strcmp(id, "admin") == 0 && strcmp(pass, "******") == 0)
        cout << "\n\n\t\t\t  !!!Login Successful!!!";
    else {
        cout << "\n\n\t\t\t!!!INVALID CREDENTIALS!!!";
        cin.ignore();
        cin.get();
        exit(-1);
    }
    h.main_menu();
    return 0;
}
