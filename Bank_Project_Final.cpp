#include <bits/stdc++.h>
#include <conio.h>   // password input (*)
#include <windows.h> // colored output
#include <unistd.h>  //  for sleep function
#define iterObj (char *)&obj, sizeof(obj)
using namespace std;

class Account
{
private:
    int AccountNumber;
    float balance;
    char type;

protected:
    char name[50];
    char nationality[50];

public:
    Account() {} // Default Constructor
    Account(int num, string naam, float bal, char t, string nat)
    {
        AccountNumber = num;
        strcpy(name, naam.c_str());
        balance = bal;
        type = t;
        strcpy(nationality, nat.c_str()); // Reason for including cctype [ in bits..]
    }
    void showData()
    {
        cout << left; // changing allignment of setw to left
        cout << setw(10) << AccountNumber << "\t" << setw(22) << name << "\t" << setw(10) << balance << "\t" << setw(1) << type << "\t" << setw(15) << nationality;
    }
    friend void create();
    friend void checkStatus(int);
    friend void modify(int);
    friend void allAccounts();
    friend void depOrWith(int, int);
    friend void deleteAccount(int);
    friend void deleteAccount();
    friend bool found(int);
};

class employee : protected Account
{
    // name and nationality inherited
private:
    int id_num;
    int salary;
    char posting[50]; // HR , manager , cashier , clerk , security guard
public:
    employee() {} // Default Constructorx
    employee(string naam, int num, int sal, string post, string nat)
    {
        strcpy(name, naam.c_str());
        strcpy(posting, post.c_str());
        id_num = num;
        salary = sal;
        strcpy(nationality, nat.c_str());
    }
    void showData()
    {
        cout << left; // changing allignment of setw to left
        cout << setw(10) << id_num << "\t" << setw(22) << name << "\t" << setw(10) << salary << "\t" << setw(10) << posting << "\t" << setw(15) << nationality;
    }
    friend void emp_create();
    friend void emp_checkStatus(int);
    friend void emp_modify(int);
    friend void allEmp();
    friend void deleteEmp(int);
    friend void deleteEmp();
    friend bool emp_found(int);
};

// TO TELL IF GIVEN ACCOUNT NUMBER EXISTS
bool found(int id)
{
    ifstream file("details.dat", ios::binary);
    Account obj; // object which reads data into itself
    while (file.read(iterObj))
    {
        if (obj.AccountNumber == id)
        {
            return 1;
        }
    }
    return 0;
}
// TO TELL IF GIVEN EMPLOYEE EXISTS
bool emp_found(int id)
{
    ifstream file("employees.dat", ios::binary);

    employee obj;              // object which reads data into itself
    while (file.read(iterObj)) // (char *)&obj, sizeof(obj)
    {
        if (obj.id_num == id)
        {
            return 1;
        }
    }
    return 0;
}

// Function To Create An Account
void create(int num)
{
    string naam, nat;
    float bal;
    char type;
    cout << "Enter Name -> ";
    fflush(stdin);
    getline(cin, naam);
    fflush(stdin);
    cout << "Enter Nationality -> ";
    getline(cin, nat);
    fflush(stdin);
    cout << "Enter account type : s(saving) , c(Current)";
    cin >> type;
    type = toupper(type);
    cout << "Enter Starting Amount : ";
    cin >> bal;
    Account temp(num, naam, bal, type, nat);
    ofstream file("details.dat", ios::binary | ios::app);
    file.write((char *)&temp, sizeof(temp));
    cout << "Account Created Successfully\n"
         << endl
         << endl;
}
// Function To Create An Employee
void emp_create(int num)
{
    string naam, nat;
    float sal;
    string post;
    cout << "Enter Name -> ";
    fflush(stdin);
    getline(cin, naam);
    fflush(stdin);
    cout << "Enter Nationality -> ";
    getline(cin, nat);
    fflush(stdin);
    cout << "Enter Position -> manager , clerk , guard, HR" << endl;
    fflush(stdin);
    getline(cin, post);
    cout << "Enter Salary : ";
    cin >> sal;
    // employee(string naam, int num, int sal, string post, string nat)
    employee temp(naam, num, sal, post, nat);
    ofstream file("employees.dat", ios::binary | ios::app);
    file.write((char *)&temp, sizeof(temp));
    cout << "Account Created Successfully\n"
         << endl
         << endl;
}

void checkStatus(int id)
{
    ifstream file("details.dat", ios::binary);
    Account obj;
    int found = 0;
    while (file.read(iterObj)) // Macro used , here iterObj ==  (char *)&obj, sizeof(obj)
    {
        if (obj.AccountNumber == id)
        {
            cout << "Account Number -> " << obj.AccountNumber << endl;
            cout << "Name           -> " << obj.name << endl;
            cout << "Balance        -> " << obj.balance << endl;
            cout << "Type           -> " << obj.type << endl;
            cout << "Nationality    -> " << obj.nationality << endl;
            break;
        }
    }
    file.close();
    cout << "\n\n";
}

void emp_checkStatus(int id)
{
    ifstream file("employees.dat", ios::binary);
    employee obj;
    int found = 0;
    while (file.read(iterObj)) // Macro used , here iterObj ==  (char *)&obj, sizeof(obj)
    {
        if (obj.id_num == id)
        {
            cout << "ID Number      -> " << obj.id_num << endl;
            cout << "Name           -> " << obj.name << endl;
            cout << "Salary         -> " << obj.salary << endl;
            cout << "Post           -> " << obj.posting << endl;
            cout << "Nationality    -> " << obj.nationality << endl;
            break;
        }
    }
    file.close();
    cout << "\n\n";
}

// Functions to deposit & withdraw money
void depOrWith(int accnum, int opt)
{
    // opt 1 -> deposit
    // opt 2 -> withdraw
    // as first need to find corresponding accnt and then modify (both write and read reqd)

    fstream file("details.dat", ios::binary | ios::in | ios::out);

    Account obj; // object which reads data into itself
    while (file.read(iterObj))
    {
        if (obj.AccountNumber == accnum)
        {
            break;
        }
    }

    if (opt == 1)
    {
        float dep;
        cout << "Current Balance = " << obj.balance << endl;

        cout << "Enter the amount of money you wish to deposit : ";
        cin >> dep;
        obj.balance += dep;
        cout << "New balance : " << obj.balance << endl;
    }
    else if (opt == 2)
    {
        int choice;
        while (choice != 0)
        {
            float with;
            cout << "Current Balance = " << obj.balance << endl;
            cout << "Enter the amount of money you wish to withdraw : ";
            cin >> with;
            if (with > obj.balance)
            {
                cout << "Not enough Balance in Account right now !" << endl;
                cout << "Press 1 to retry and 0 to return !" << endl;
                cin >> choice;
            }
            else
            {
                obj.balance -= with;
                cout << "Transaction Successfull !!!" << endl;
                cout << "New balance : " << obj.balance << endl;
                cout << "Press 1 to WITHDRAW more money & 0 to return! " << endl;
                cin >> choice;
            }
        }
    }
    // now we are one object ahead of the account needed to be modified , therefor move
    // back one object using seekp
    file.seekp(file.tellg() - std::streamoff(sizeof(obj)), ios::beg); // seekP(as we will put)  current position from where we are Getting - obj size bytes ,
    file.write(iterObj);
    file.close();
    cout << "\n\n\n";
}

// Function to modify an existing account
void modify(int id)
{
    fstream file("details.dat", ios::binary | ios::in | ios::out);
    if (!file)
    {
        cout << "File could not be opened as no account exists yet !" << endl;
        return;
    }
    Account obj; // object which reads data into itself
    bool found = 0;
    while (file.read(iterObj))
    {
        if (obj.AccountNumber == id)
        {
            found = 1;
            break;
        }
    }
    if (found == 0)
    {
        cout << "No account with this account number exists !\n\n\n"
             << endl;
        return;
    }
    string naam, nat;
    float bal;
    char type;
    cout << "Enter new Name -> ";
    fflush(stdin);
    getline(cin, naam);
    fflush(stdin);
    cout << "Enter updated Nationality -> ";
    getline(cin, nat);
    fflush(stdin);
    cout << "Enter new account type : s(saving) , c(Current)";
    cin >> type;
    type = toupper(type);
    cout << "Enter new current balance : ";
    cin >> bal;
    int accnum = obj.AccountNumber;
    Account temp(accnum, naam, bal, type, nat); // new temp object which will overwrite data of obj
    file.seekp(file.tellg() - std::streamoff(sizeof(obj)), ios::beg);
    file.write((char *)&temp, sizeof(temp));
    file.close();
    cout << "\n\n";
}

// Function to modify an existing Employee
void emp_modify(int id)
{
    fstream file("employees.dat", ios::binary | ios::in | ios::out);
    if (!file)
    {
        cout << "File could not be opened as no account exists yet !" << endl;
        return;
    }
    employee obj; // object which reads data into itself
    bool found = 0;
    while (file.read(iterObj))
    {
        if (obj.id_num == id)
        {
            found = 1;
            break;
        }
    }
    if (found == 0)
    {
        cout << "No Employee with this ID number exists !\n\n\n"
             << endl;
        return;
    }

    string naam, nat;
    float sal;
    string post;
    cout << "Enter new Name -> ";
    fflush(stdin);
    getline(cin, naam);
    fflush(stdin);
    cout << "Enter new Nationality -> ";
    getline(cin, nat);
    fflush(stdin);
    cout << "Enter new Position -> manager , clerk , guard, HR" << endl;
    fflush(stdin);
    getline(cin, post);
    cout << "Enter updated Salary : ";
    cin >> sal;
    int num = obj.id_num;
    // employee(string naam, int num, int sal, string post, string nat)
    employee temp(naam, num, sal, post, nat);
    file.seekp(file.tellg() - std::streamoff(sizeof(obj)), ios::beg);
    file.write((char *)&temp, sizeof(temp));
    file.close();
    cout << "\n\n";
}

// Function to delete an existing account
void deleteAccount(int id)
{
    fstream file("details.dat", ios::binary | ios::in | ios::out);
    ofstream temp("temp.dat", ios::binary | ios::app);
    if (!file)
    {
        cout << "File could not be opened as no account exists yet !" << endl;
        return;
    }
    Account obj; // object which reads data into itself
    // to delete an account we copy all the records to a new dat file except that record
    while (file.read(iterObj))
    {
        if (obj.AccountNumber != id)
        {
            temp.write(iterObj);
        }
    }
    file.close();
    temp.close();
    remove("details.dat");
    rename("temp.dat", "details.dat");
    cout << "Account Deleted Successfully !!\n"
         << endl;
}

// Function Polymorphism to delete all existing account
void deleteAccount()
{
    fstream file("details.dat", ios::binary | ios::in | ios::out);
    ofstream temp("temp.dat", ios::binary | ios::app);
    if (!file)
    {
        cout << "File could not be opened as no account exists yet !" << endl;
        return;
    }
    file.close();
    temp.close();
    remove("details.dat");
    rename("temp.dat", "details.dat");
    cout << "Accounts Deleted Successfully !!\n"
         << endl;
}

// Function to delete an existing employee
void deleteEmp(int id)
{
    fstream file("employees.dat", ios::binary | ios::in | ios::out);
    ofstream temp("temp.dat", ios::binary | ios::app);
    if (!file)
    {
        cout << "File could not be opened as no account exists yet !" << endl;
        return;
    }
    employee obj; // object which reads data into itself
    // to delete an account we copy all the records to a new dat file except that record
    while (file.read(iterObj))
    {
        if (obj.id_num != id)
        {
            temp.write(iterObj);
        }
    }
    file.close();
    temp.close();
    remove("employees.dat");
    rename("temp.dat", "employees.dat");
    cout << "employee Deleted Successfully !!\n"
         << endl;
}
// Function to delete all existing employee
void deleteEmp()
{
    fstream file("employees.dat", ios::binary | ios::in | ios::out);
    ofstream temp("temp.dat", ios::binary | ios::app);
    if (!file)
    {
        cout << "File could not be opened as no account exists yet !" << endl;
        return;
    }
    file.close();
    temp.close();
    remove("employees.dat");
    rename("temp.dat", "employees.dat");
    cout << "employee Deleted Successfully !!\n"
         << endl;
}
// Function to Read All current Accounts
void allAccounts()
{
    ifstream file("details.dat", ios::binary);
    Account obj;
    cout << "ACCOUNT No.\tNAME\t\t        BALANCE\t       TYPE\tNATIONALITY" << endl;
    cout << "****************************************************************************\n";
    while (file.read(iterObj))
    {
        obj.showData();
        cout << endl;
    }
}
void allEmp()
{
    ifstream file("employees.dat", ios::binary);
    employee obj;
    cout << "\n\nIdentity No.\t    NAME\t\tBALANCE\t        POST\t        NATIONALITY" << endl;
    cout << "***********************************************************************************\n";
    while (file.read(iterObj))
    {
        obj.showData();
        cout << endl;
    }
    cout << "\n\n";
}

// if user is not an admin!
void UserLogin()
{
    system("Color 6A");
    int accnum;
    int next;
    cout << "Enter Account Number " << endl;
    cin >> accnum;
    if (found(accnum))
    {
        while (next != 0)
        {
            int choice;
            cout << "Press 1 if you want to get details of your account " << endl;
            cout << "Press 2 if you want to deposit money into your account " << endl;
            cout << "Press 3 if you want to withdraw money from your account " << endl;
            cin >> choice;
            if (choice == 1)
            {
                checkStatus(accnum);
            }
            else if (choice == 2)
            {
                depOrWith(accnum, 1);
            }
            else if (choice == 3)
            {
                depOrWith(accnum, 2);
            }
            else
            {
                cout << "Please Enter valid input !!" << endl;
            }
            cout << "Press 1 to work again on your account  and 0  to return to main menu !" << endl;
            cin >> next;
        }
    }
    else
    {
        cout << "No Account exists corresponding to account number : " << accnum << endl;
        cout << "Press 1 to try again and 0  to return to main menu !" << endl;
        cin >> next;
        if (next == 0)
        {
            return;
        }
        else
        {
            UserLogin();
        }
    }
}

int count_unsuc = 0;
// if user is an admin !
void AdminLogin()
{
    system("Color 4F");
    string naam;
    int next;
    int funcpick = 1;
    cout << "\n\n\n"
         << endl;
    cout << "Enter Name : ";
    fflush(stdin);
    getline(cin, naam);
    cout << "Enter Password : ";

    char s[5] = {0};

    for (int i = 0; i < 5; i++)
    {
        fflush(stdin);
        s[i] = _getch();
        _putch('*');
        if (s[i] == 13)
            break;
    };
    // getchar();
    // s holds password entered by user
    int access = 1;
    string correctPassword = "12345";
    for (int i = 0; i < 5; i++)
    {
        if (s[i] != correctPassword[i])
        {
            access = 0;
            break;
        }
    }

    if (naam == "Sorav" && access)
    {
        cout << "\nSUCCESSFULL LOGIN!!\n\n\n";
    }
    else
    {

        cout << "\nLogin Unsuccessfull!! Either Admin name or password is incorrect!" << endl
             << endl;
        cout << "You have " << 2 - count_unsuc << " more tries !" << endl;
        count_unsuc++;
        if (count_unsuc == 3)
        {
            cout << "Due to Security Reason you have to wait for 10 seconds for next try!!\n"
                 << endl;
            count_unsuc = 0;
            sleep(10);
        }

        cout << "\n Press 2 to try again and 0 to return to main menu " << endl;
        cin >> next;
        if (next == 2)
        {
            AdminLogin();
        }
        else
        {
            return;
        }
    }

    system("Color 5F");
    int emp_accnt;
    cout << "Press 1 if you want to work with customer Accounts and 2 for bank employees\n";
    cin >> emp_accnt;

    if (emp_accnt == 1)
    {
        while (funcpick != 7)
        {
            int accnum;
            cout << "\n\n\n";
            cout << "Press 1 : CREATE ACCOUNT " << endl;
            cout << "Press 2 : View Specific Account " << endl;
            cout << "Press 3 : View All Accounts " << endl;
            cout << "Press 4 : Modify An Account " << endl;
            cout << "Press 5 : Close An Account " << endl;
            cout << "Press 6 : Close All Accounts " << endl;
            cout << "Press 7 : To Log Out " << endl;
            cin >> funcpick;
            switch (funcpick)
            {
            case 1:
                cout << "Enter Account Number : ";
                cin >> accnum;
                if (found(accnum))
                {
                    cout << "Account Number unavailable !!\n"
                         << endl;
                }
                else
                {
                    create(accnum);
                }
                break;
            case 2:
                cout << "Enter Account Number : ";
                cin >> accnum;
                if (found(accnum))
                {
                    checkStatus(accnum);
                }
                else
                {
                    cout << "Invalid Account Number !" << endl;
                }
                break;
            case 3:
                allAccounts();
                break;
            case 4:
                cout << "Enter Account Number : ";
                cin >> accnum;
                if (found(accnum))
                {
                    modify(accnum);
                }
                else
                {
                    cout << "Invalid Account Number !" << endl;
                }
                break;
            case 5:
                cout << "Enter Account Number : ";
                cin >> accnum;
                if (found(accnum))
                {
                    deleteAccount(accnum);
                }
                else
                {
                    cout << "Invalid Account Number !" << endl;
                }
                break;
            case 6:
                int p;
                cout << "press 1 to confirm if you wish to delete all the data in the file!!" << endl;
                cin >> p;
                if (p == 1)
                {
                    deleteAccount();
                }
                break;
            case 7:
                cout << "LOGOUT SUCCESSFULL!!!" << endl;
                cout << "Bye Admin!!" << endl;
                break;
            }
        }
    }
    else if (emp_accnt == 2)
    {
        while (funcpick != 7)
        {
            int idnum;
            cout << "\n\n\n";
            cout << "Press 1 : HIRE NEW EMPLOYEE " << endl;
            cout << "Press 2 : View Specific EMPLOYEE " << endl;
            cout << "Press 3 : View All Employees " << endl;
            cout << "Press 4 : Update An Employee " << endl;
            cout << "Press 5 : Release An Employee " << endl;
            cout << "Press 6 : Release All Employee " << endl;
            cout << "Press 7 : To Log Out " << endl;
            cin >> funcpick;
            switch (funcpick)
            {
            case 1:
                cout << "Enter ID Number : ";
                cin >> idnum;
                if (emp_found(idnum))
                {
                    cout << "ID Number unavailable !!\n"
                         << endl;
                }
                else
                {
                    emp_create(idnum);
                }
                break;
            case 2:
                cout << "Enter ID Number : ";
                cin >> idnum;
                if (emp_found(idnum))
                {
                    emp_checkStatus(idnum);
                }
                else
                {
                    cout << "Invalid ID Number !" << endl;
                }
                break;
            case 3:
                allEmp();
                break;
            case 4:
                cout << "Enter ID Number : ";
                cin >> idnum;
                if (emp_found(idnum))
                {
                    emp_modify(idnum);
                }
                else
                {
                    cout << "Invalid ID Number !" << endl;
                }
                break;
            case 5:
                cout << "Enter ID Number : ";
                cin >> idnum;
                if (emp_found(idnum))
                {
                    deleteEmp(idnum);
                }
                else
                {
                    cout << "Invalid ID Number !" << endl;
                }
                break;
            case 6:
                int p;
                cout << "press 1 to confirm if you wish to delete all the data in the file!!" << endl;
                cin >> p;
                if (p == 1)
                {
                    deleteEmp();
                }
                break;
            case 7:
                cout << "LOGOUT SUCCESSFULL!!!" << endl;
                cout << "Bye Admin!!" << endl;
                break;
            }
        }
    }
}
int main()
{
    int mainlogin = 1;
    while (mainlogin >= 1 && mainlogin <= 3)
    {
        system("Color 1E");

        cout << "Press 1 for user login " << endl;
        cout << "Press 2 for admin login " << endl;
        cout << "Press 3 to exit the program " << endl;
        cin >> mainlogin;
        switch (mainlogin)
        {
        case 1:
            UserLogin();
            break;
        case 2:
            AdminLogin();
            break;
        case 3:
            cout << "Thanks For Your Visit !!!! CYAA!" << endl;
            exit(0);
        default:
            cout << "Please Select A Valid Input!!" << endl;
        }
    }

    // employee emp;
    // emp_create(21103144);
    // allEmp();

    return 0;
}