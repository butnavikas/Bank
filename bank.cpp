#include<bits/stdc++.h>
#include<random>
using namespace std;


class Bank{
    private:
        static int nextId ;
    public:
        int c_id;
        string c_name;
        string phone;
        string pin;

    void initializeId() {
    ifstream file("customers.txt");
    int id;
    string name, phone, pin;

    while (file >> id >> name >> phone >> pin) {
        nextId = id + 1; //it will update each time new acc is created
    }
    file.close();
}



//create account
//working pefectly
    void createaccount(){
    cout<<"\n NEW ACCOUNT \n";
    cout<<"Enter your name without spaces : ";
    cin>>c_name;

    cout<<"Enter your phone no : ";
    cin>>phone;

    cout<<"Create your 4 digit pin : ";
    cin>>pin;

    if(pin.length() != 4){
        cout<<"Invalid Pin, must be 4 digits"<<endl;
        return;
    }
    c_id = nextId++;
    //create and write 
    ofstream file("customers.txt",ios::app);
    file<<c_id<<" "<<c_name<<" "<<phone<<" "<<pin<<endl;
    file.close();

    ofstream file1("accounts.txt",ios::app);
    file1<<c_id<<" "<<0<<endl;
    file1.close();

    cout<<"Your account created succesfully"<<endl;
    cout<<"Your account no. is : "<<c_id<<endl;
    cout<<"Thank you for beginnig your journey with V Bank"<<endl;
  

}



//login page
//working pefectly
int login(){
   //for taking input
   int accountno;
   string password;
   //for searching
   int c_id,id;
   string c_name,name;
   string phone;
   string pin;
   //file pass or fail
   bool userfound = false;
   
    cout<<"\n LOGIN \n";
    cout<<"Enter your Customer Id : ";
    cin>>accountno;
    cout<<"Enter your PIN : ";
    cin>>password;
    ifstream infile("customers.txt");
    while(infile>>c_id>>c_name>>phone>>pin){
        if(accountno == c_id && password == pin){
            id = c_id;
            name =c_name ;
            userfound = true ;
            
        }   
    }

    infile.close();
        if(userfound){
            cout<<"You have logged in Successfully"<<endl;
            cout<<"Welcome "<<name<<endl;
            return id;
        }else {
        cout<<"Invalid account no. or password . Please try again"<<endl;
        
        }
        return -1;
}





//deposit money
//working pefectly
void deposit() {
    int c_id = login();
    if (c_id == -1) return;

   cout<<"\n DEPOSIT \n";
   
    double amt;
    cout << "Enter the amount of money you want to add: ";
    cin >> amt;

    vector<pair<int, double>> accounts;
    int acno;
    double balance;

    // READ
    ifstream in("accounts.txt");
    while (in >> acno >> balance) {
        accounts.push_back({acno, balance});
    }
    in.close();

    // MODIFY
    for (auto &acc : accounts) {
        if (acc.first == c_id) {
            acc.second += amt;
            break;
        }
    }

    // WRITE BACK
    ofstream out("accounts.txt");
    for (auto &acc : accounts) {
        out << acc.first << " " << acc.second << endl;
    }
    out.close();

    ofstream tfile("transactions.txt", ios::app);
    tfile << c_id << " CREDIT " << amt << endl;
    tfile.close();
    cout << "Deposit successfull\n";

    ifstream i("accounts.txt");
    while (i >> acno >> balance) {
        if(acno == c_id){
            cout<<"Your balance is :"<<balance<<endl;
        }
    }
    i.close();
    cout<<"Thank you for banking with us"<<endl;
    
}

//working pefectly
void withdraw(){
    int c_id = login();
    if(c_id == -1) return;

    cout<<"\n WITHDRAW \n";
    double amt;
    cout<<"Enter the amount of money you want to Withdraw : ";
    cin>>amt;

    vector<pair<int, double>> accounts;
    int acno;
    double balance;
    bool found = false;

    // READ
    ifstream in("accounts.txt");
    while (in >> acno >> balance) {
        accounts.push_back({acno, balance});
    }
    in.close();

    // CHECK & MODIFY
    for (auto &acc : accounts) {
        if (acc.first == c_id) {
            found = true;
            if (amt > acc.second) {
                cout<<"Insufficient Balance"<<endl;
                return;
            }
            acc.second -= amt;
            cout<<"Money Withdrawal Successful : "<<amt<<endl;
            cout<<"Remaining Balance : "<<acc.second<<endl;
            break;
        }
    }

    // WRITE BACK
    ofstream out("accounts.txt");
    for (auto &acc : accounts) {
        out << acc.first << " " << acc.second << endl;
        
    }
    out.close();

    // TRANSACTION LOG
    ofstream tfile("transactions.txt", ios::app);
    tfile << c_id << " DEBIT " << amt << endl;
    tfile.close();

    cout<<"Thank you for banking with us"<<endl;
}


//transfer
//working perfectly
void transfer(){
    int c_id = login();
    int acno;
    double balance;
    int benificiary ;
    double amt;
    vector<pair<int, double>> accounts;
    cout<<"Enter the account no. of benificiary : ";
    cin>>benificiary;
    cout<<"Enter the amount you want to transfer : ";
    cin>>amt;
    bool found = false;

     // READ
    ifstream in("accounts.txt");
    while (in >> acno >> balance) {
        accounts.push_back({acno, balance});
    }
    in.close();

    // CHECK & MODIFY
    for (auto &acc : accounts) {
        if (acc.first == c_id) {
            found = true;
            if (amt > acc.second) {
                cout<<"Insufficient Balance"<<endl;
                return;
            }
            acc.second -= amt;
            cout<<"Money Transferred Successful : "<<amt<<endl;
            cout<<"Remaining Balance : "<<acc.second<<endl;
            break;
        }



    }

    // WRITE BACK
    ofstream out("accounts.txt");
    for (auto &acc : accounts) {
        out << acc.first << " " << acc.second << endl;
        
    }
    out.close();

    // TRANSACTION LOG
    ofstream tfile("transactions.txt", ios::app);
    tfile << c_id << " TRANSFERRED " << amt<<" TO "<<benificiary<< endl;
    tfile.close();

    //deposit in benificiary

    vector<pair<int, double>> accounts1;
    int acno1;
    double balance1;

    // READ
    ifstream in1("accounts.txt");
    while (in1 >> acno1 >> balance1) {
        accounts1.push_back({acno1, balance1});
    }
    in1.close();

    // MODIFY
    for (auto &acc1 : accounts1) {
        if (acc1.first == benificiary) {
            acc1.second += amt;
            break;
        }
    }

    // WRITE BACK
    ofstream out1("accounts.txt");
    for (auto &acc1 : accounts1) {
        out1 << acc1.first << " " << acc1.second << endl;
    }
    out1.close();

    ofstream tfile1("transactions.txt", ios::app);
    tfile1 << benificiary << " TRANSFERRED " << amt <<" FROM " <<c_id << endl;
    tfile1.close();
    

            ifstream i1("accounts.txt");
    while (i1 >> acno >> balance) {
        if(acno == benificiary){
            balance += amt;
           break;
        }
    }
    i1.close();

    cout<<"Thank you for banking with us"<<endl;
}

void balance(){
    int c_id = login();
    int id;
    double balance,b1;
    ifstream i("accounts.txt");
    while(i >> id >> balance){
        if(c_id == id){
            cout<<"Your Balance is : "<<balance<<endl;

            break;
        }
    }
    i.close();
    cout<<"Thank you for banking with us"<<endl;

}

};

class Account {
public:
    int id;
    string name;
    string phone;
    string pin;
    double balance;

    void display() {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Balance : " << balance << endl;
    }
};

//customers file for customerid ,name, phone, pin
//accounts file for customerid , balance
//transactions file for customer id, type(deposit,withdraw,transfer) , amount
int Bank::nextId = 1001;
int main(){
    Bank bank;
    int choice;
    cout<<"\n Enter your choice \n";
    cout<<"Press 1 for Creating  a account"<<endl;
    cout<<"Press 2 for depositing money"<<endl;
    cout<<"Press 3 for transfering money"<<endl;
    cout<<"Press 4 for withdrawing money"<<endl;
    cout<<"Press 5 for checking balance"<<endl;

    cin>>choice;
    switch(choice){
        case 1:
        bank.initializeId();   
        bank.createaccount();
        break;
        case 2: bank.deposit();
        break;
        case 3: bank.transfer();
        break;
        case 4: bank.withdraw();
        break;
        case 5: bank.balance();
        break;
        default : cout<<"Invalid button"<<endl;
        return 0;

    }
    return 0;
}




