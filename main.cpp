
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
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
        date = "";
        category = "";
        description = "";
        amount = 0;
    }

    Expense(string date, string category, string description, double amount)
    {
        this->date = date;
        this->category = category;
        this->description = description;
        this->amount = amount;
    }

    void display() const
    {
        cout << "Date: " << date << endl;
        cout << "Category: " << category << endl;
        cout << "Description: " << description << endl;
        cout << "Amount: " << amount << endl;
    }

    double getAmount() const
    {
        return amount;
    }

    void writeToFile(ofstream& fout) const
    {
        fout << date << endl;
        fout << category << endl;
        fout << description << endl;
        fout << setprecision(17) << amount << endl;
    }

    bool readFromFile(ifstream& fin)
    {
        string amountText;

        if (!getline(fin, date)) return false;
        if (!getline(fin, category)) return false;
        if (!getline(fin, description)) return false;
        if (!getline(fin, amountText)) return false;

        istringstream amountInput(amountText);
        char extra;

        if (!(amountInput >> amount) || (amountInput >> extra))
            return false;

        return true;
    }
};

// Rewrite the file after deleting an expense
bool rewriteFile(const Expense expenses[], int count)
{
    ofstream fout("expenses.txt");

    if (!fout.is_open())
        return false;

    for (int i = 0; i < count; i++)
    {
        expenses[i].writeToFile(fout);
    }

    fout.close();

    return !fout.fail();
}

int main()
{
    Expense expenses[100];

    int count = 0;
    int choice = 0;
    double total = 0;

    // Load previously saved expenses
    ifstream fin("expenses.txt");

    if (fin.is_open())
    {
        while (count < 100)
        {
            Expense savedExpense;

            if (!savedExpense.readFromFile(fin))
                break;

            expenses[count] = savedExpense;
            total += savedExpense.getAmount();
            count++;
        }

        fin.close();
    }

    if (count > 0)
        cout << count << " previous expenses loaded." << endl;

    string input;

    do
    {
        cout << "\n***** DAILY EXPENSE TRACKER *****\n";
        cout << "1. Add Expenses." << endl;
        cout << "2. View All Expenses." << endl;
        cout << "3. Show Total Spending." << endl;
        cout << "4. Delete Expenses." << endl;
        cout << "5. EXIT" << endl;

        cout << "\nEnter your choice: ";

        if (!getline(cin, input))
            break;

        istringstream choiceInput(input);
        char extra;

        choice = 0;

        if (!(choiceInput >> choice) || (choiceInput >> extra))
        {
            cout << "Invalid choice. Enter a number from 1 to 5." << endl;
            continue;
        }

        switch (choice)
        {
            case 1:
            {
                if (count >= 100)
                {
                    cout << "Storage is full!" << endl;
                    break;
                }

                string date, category, description, amountText;
                double amount;

                cout << "Enter date: ";
                getline(cin, date);

                cout << "Enter category: ";
                getline(cin, category);

                cout << "Enter description: ";
                getline(cin, description);

                if (date.empty() || category.empty() || description.empty())
                {
                    cout << "Fields cannot be empty!" << endl;
                    break;
                }

                cout << "Enter amount: ";
                getline(cin, amountText);

                istringstream amountInput(amountText);

                if (!(amountInput >> amount) ||
                    (amountInput >> extra) || amount <= 0)
                {
                    cout << "Invalid amount! Enter a positive number." << endl;
                    break;
                }

                Expense newExpense(date, category, description, amount);

                ofstream fout("expenses.txt", ios::app);

                if (!fout.is_open())
                {
                    cout << "Could not open expenses.txt!" << endl;
                    break;
                }

                newExpense.writeToFile(fout);
                fout.close();

                if (fout.fail())
                {
                    cout << "Could not save expense!" << endl;
                    break;
                }

                expenses[count] = newExpense;
                total += amount;
                count++;

                cout << "\nExpense added successfully!" << endl;
                expenses[count - 1].display();

                break;
            }

            case 2:
            {
                cout << "\n======= ALL EXPENSES =======" << endl;

                if (count == 0)
                {
                    cout << "No expenses recorded yet." << endl;
                }
                else
                {
                    for (int i = 0; i < count; i++)
                    {
                        cout << "\nExpense " << i + 1 << endl;
                        expenses[i].display();
                        cout << "-----------------------" << endl;
                    }
                }

                break;
            }

            case 3:
            {
                cout << "\nTotal Spending: " << total << endl;
                break;
            }

            case 4:
            {
                if (count == 0)
                {
                    cout << "No expenses to delete!" << endl;
                    break;
                }

                cout << "\n======= ALL EXPENSES =======" << endl;

                for (int i = 0; i < count; i++)
                {
                    cout << "\nExpense " << i + 1 << endl;
                    expenses[i].display();
                }

                string deleteText;
                int deleteIndex;

                cout << "\nEnter expense number to delete: ";
                getline(cin, deleteText);

                istringstream deleteInput(deleteText);

                if (!(deleteInput >> deleteIndex) ||
                    (deleteInput >> extra))
                {
                    cout << "Invalid input! Enter a whole number." << endl;
                    break;
                }

                if (deleteIndex < 1 || deleteIndex > count)
                {
                    cout << "Invalid expense number!" << endl;
                    break;
                }

                Expense updatedExpenses[100];

                int newCount = 0;
                double removedAmount =
                    expenses[deleteIndex - 1].getAmount();

                for (int i = 0; i < count; i++)
                {
                    if (i != deleteIndex - 1)
                    {
                        updatedExpenses[newCount] = expenses[i];
                        newCount++;
                    }
                }

                if (!rewriteFile(updatedExpenses, newCount))
                {
                    cout << "Could not update expenses.txt!" << endl;
                    break;
                }

                for (int i = 0; i < newCount; i++)
                {
                    expenses[i] = updatedExpenses[i];
                }

                count = newCount;
                total -= removedAmount;

                cout << "Expense deleted successfully!" << endl;

                break;
            }

            case 5:
            {
                cout << "Exiting Daily Expense Tracker." << endl;
                break;
            }

            default:
            {
                cout << "Wrong choice! Enter a number from 1 to 5." << endl;
            }
        }

    } while (choice != 5);

    return 0;
}
