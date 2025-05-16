#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;

const int NUM_ITEMS = 4;       //Four types of goods
const int MAX_RECORDS = 1000;  // Maximum number of records
string itemNames[NUM_ITEMS] = { "Fish", "Veggie", "Utensils", "Rice" };

struct Transaction {
    string timestamp;
    string type;      // Restock and Sale
    int itemIndex;    // item
    int quantity;     // amount
};

Transaction transactions[MAX_RECORDS];
int transactionCount = 0;
int stock[NUM_ITEMS] = { 0 };  // Current Inventory

//  Localtime
string getTimestamp() {
    time_t tt = time(nullptr);
    struct tm ti;
    localtime_s(&ti, &tt);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S", &ti);
    return string(buffer);
}

// load history
void loadHistory() 
{
    ifstream file("RecordData.txt");
    if (file) 
    {
        string line;
        while (getline(file, line) && transactionCount < MAX_RECORDS) 
        {
            istringstream iss(line);
            Transaction t;
            if (iss >> t.timestamp >> t.type >> t.itemIndex >> t.quantity) 
            {
                transactions[transactionCount++] = t;
                // Update Inventory
                if (t.type == "Restock") 
                {
                    stock[t.itemIndex] += t.quantity;
                }
                else if (t.type == "Sale") 
                {
                    stock[t.itemIndex] -= t.quantity;
                }
            }
        }
    }
}

// Save record history
void saveHistory() 
{
    ofstream file("RecordData.txt");
    for (int i = 0; i < transactionCount; ++i) 
    {
        file << transactions[i].timestamp << " "
            << transactions[i].type << " "
            << transactions[i].itemIndex << " "
            << transactions[i].quantity << endl;
    }
}

// Show stcok
void displayStock() 
{
    cout << "\nCurrent Inventory:" << endl;
    for (int i = 0; i < NUM_ITEMS; ++i) 
    {
        cout << i + 1 << ". " << itemNames[i] << ": " << stock[i] << endl;
    }
    cout << endl;
}

// Restock
void restockItem() 
{
    int itemIndex, quantity;
    cout << "\nSelect item to restock:" << endl;
    displayStock();
    cout << "Enter item number (1-4): ";
    cin >> itemIndex;
    itemIndex--;

    if (itemIndex < 0 || itemIndex >= NUM_ITEMS) 
    {
        cout << "Invalid item number!" << endl;
        return;
    }

    cout << "Enter quantity to restock: ";
    cin >> quantity;
    if (quantity <= 0) 
    {
        cout << "Quantity must be positive!" << endl;
        return;
    }

    stock[itemIndex] += quantity;
    transactions[transactionCount++] = { getTimestamp(), "Restock", itemIndex, quantity };
    cout << "Restock successful! " << endl;
}

// Sale
void sellItem() 
{
    int itemIndex, quantity;
    cout << "\nSelect item to sell:" << endl;
    displayStock();
    cout << "Enter item number (1-4): ";
    cin >> itemIndex;
    itemIndex--;

    if (itemIndex < 0 || itemIndex >= NUM_ITEMS) 
    {
        cout << "Invalid item number!" << endl;
        return;
    }

    cout << "Enter quantity to sell: ";
    cin >> quantity;
    if (quantity <= 0) 
    {
        cout << "Quantity must be positive!" << endl;
        return;
    }

    if (quantity > stock[itemIndex]) 
    {
        cout << "Insufficient stock!" << endl;
        return;
    }

    stock[itemIndex] -= quantity;
    transactions[transactionCount++] = { getTimestamp(), "Sale", itemIndex, quantity };
    cout << "Sale successful!\n" << endl;
}

// Show history
void showTransactions(const string& type) {
    cout << "\nTransaction History [" << type << "]" << endl;
    for (int i = 0; i < transactionCount; ++i) {
        if (transactions[i].type == type || type == "All") 
        {
            cout << "[" << transactions[i].timestamp << "] "
                << transactions[i].type << " "
                << itemNames[transactions[i].itemIndex] << " "
                << transactions[i].quantity << endl;
        }
    }
    cout << endl;
}

int main() 
{
    loadHistory();  // download history

    //Verify User( GUI )
    while (true) 
    {
        string userName;
        cout << "Enter your account name: ";
        cin >> userName;
        if (userName != "Tim")  //Assume the user name is Tim
        {
            cout << "User does not exist, please retry.\n" << endl;
            continue;
        }

        cout << "Please enter your password: ";
        int password;
        cin >> password;
        if (password == 123) //Assume the password is 123
        {
            cout << "Welcome back! Tim" << endl;
            break;
        }
        else 
        {
            cout << "Wrong password, please retry." << endl;
        }
    }

    // Menu
    while (true) 
    {
        cout << "****** Inventory Management System ******" << endl
            << "1. Current Inventory" << endl
            << "2. Sell Items" << endl
            << "3. Restock Items" << endl
            << "4. View Sales History" << endl
            << "5. View Restock History" << endl
            << "6. Exit" << endl
            << "Enter your choice (1-6): ";

        int choice;
        cin >> choice;

        if (choice == 1) //Current Inventory
        {
            displayStock();
        }
        else if (choice == 2) // Sell Items
        {
            sellItem();
            displayStock();
        }
        else if (choice == 3) //  Restock Items
        {
            restockItem();
            displayStock();
        }
        else if (choice == 4)//View Sales History
        {
            showTransactions("Sale");
        }
        else if (choice == 5) // View Restock History
        {
            showTransactions("Restock");
        }
        else if (choice == 6) // Exit
        {
            saveHistory();
            cout << "\nData saved. Goodbye!" << endl;
            return 0;
        }
        else//let the user to re-enter
        {
            cout << "Invalid choice! Please enter 1-6.\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
