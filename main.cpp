# include <iostream>
# include <string>
using namespace std;

class Expense
{
 private: 
  string date;
  string category;
  string description;
  double amount;
 public:
  Expense(string date, string category, string description, double amount)
{
  this-> date=date;
  this->category=category;
  this-> description=description;
  this-> amount= amount;
}
void display()
{
 cout<< "Date : "<<date<<endl;
 cout<<"Category : "<<category<<endl;
 cout<<"Description : "<<description<<endl;
  cout<<"Amout : "<<amount<<endl;
}
  
};
int main()
{
    string date;
  string category;
  string description;
  double amount;
    
  int choice=0 ;
   do
     {
       cout<<"\n****MENUE****\n"<<endl;
          cout<<"1. Add Expenses."<<endl;
          cout<<"2. View all expenses."<<endl;
          cout<<"3. Show total spending "<<endl;
          cout<<"4. Show categorywise spending."<<endl;
           cout<<"5. Delete Expenses. "<<endl;
           cout<<"6. EXIT"<<endl;

          cout<<"Enter your choice : "<<endl;
         cin>>choice;
       switch(choice)
         {
           case 1:  
             cin.ignore();
            cout<<"Added Expenses.."<<endl;
               cout<<"Date :"<<date<<endl;
            getline(cin,date);
               cout<<"Category :"<<category<<endl;
               getline(cin,category);
               cout<<"Description : "<<description<<endl;
               getline(cin, description);
               cout<<"Amount Spend : "<<endl;
               cin>>amount;

            Expense e1(date,category,description, amount);
            e1.display();
           break;

           case 2: cout<<"=======list of all expenses======"<<endl;
           break;

           case 3: cout<<"Total speanding "<< endl;
               break;

           case 4:
           cout<<"Categorized spendings"<<endl;
           break;

           case 5:
           cout<<"Deleted expenses"<<endl;
           break;

           case 6:
           cout<<"EXIT"<<endl;
          break;

           default:
           cout<<"Wrong Choice."<<endl;
         }
        
     }while (choice != 6);

  return 0;
}
