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
Expense()
{
  date ="";
 category="";
  description = "";
  amount = 0;
}
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
  cout<<"Amount : "<<amount<<endl;
}
  
};
int main()
{
    string date;
  string category;
  string description;
  double amount;

 Expense expenses[100];
 int count=0;
    
  int choice=0 ;
 double total=0;
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
           case 1:  {
             cin.ignore();
            cout<<"Added Expenses.."<<endl;
               cout<<"Date :"<<endl;
            getline(cin,date);
               cout<<"Category :"<<endl;
               getline(cin,category);
               cout<<"Description : "<<endl;
               getline(cin, description);
               cout<<"Amount Spend : "<<endl;
               cin>>amount;

         if (count<100)
         {
          expenses[count] = Expense(date,category, description,amount);
                total=total+amount;
          expenses[count].display();
          count++;
         }
            else
         {
          cout<<"\nSorry the Storage is Full!\n";
         }
            cout<<"\n================Information====================\n";
            
           break;
         }

           case 2: cout<<"=======list of all expenses======"<<endl;
               if (count==0 )
               {
                   cout<<"No Expenses recorded yet!"<<endl;
               }
               else
               {
                   for (int i=0; i< count ; i++)
                       {
                              cout<<"===========================\n";
                       cout<<"Expenses\n"<<i+1 <<endl;
                       expenses[i].display();
                       }
               }
           break;

           case 3: cout<<"Total speanding: "<<total<< endl;
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
