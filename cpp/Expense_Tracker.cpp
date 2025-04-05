#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <map> // <-- NEW: for total by category

using namespace std;

// Fixed categories
const vector<string> CATEGORIES = {"Food", "Transport", "Shopping", "Entertainment", "Utilities", "Healthcare", "Other"};
const string FILENAME = "expenses.csv"; // CSV file name

// Helper to make string lowercase
string to_lower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Function to check if category is valid (case-insensitive)
bool is_valid_category(const string& category) {
    for (const auto& cat : CATEGORIES) {
        if (to_lower(cat) == to_lower(category)) {
            return true;
        }
    }
    return false;
}

// Function to display all categories
void show_categories() {
    cout << "\nAvailable Categories:\n";
    for (const auto& cat : CATEGORIES) {
        cout << cat << ", ";
    }
    cout << "\n";
}

// Function to add an expense
void add_expense() {
    try {
        string date, category, description;
        double amount;

        cout << "Enter date (YYYY-MM-DD): ";
        cin >> date;
        cout << "Enter amount: ";
        cin >> amount;
        if (cin.fail() || amount < 0) {
            throw invalid_argument("Invalid amount entered!");
        }

        cin.ignore(); // Clear buffer
        show_categories();
        cout << "Enter category name exactly as shown above: ";
        getline(cin, category);

        if (!is_valid_category(category)) {
            throw invalid_argument("Invalid category! Please choose from the list.");
        }

        cout << "Enter description: ";
        getline(cin, description);

        // Write to CSV
        ofstream file(FILENAME, ios::app);
        if (file.is_open()) {
            file << date << "," << fixed << setprecision(2) << amount << "," << category << "," << description << endl;
            file.close();
            cout << "Expense added successfully under '" << category << "' category!\n";
        } else {
            cout << "❌ Error: Could not open file.\n";
        }

    } catch (const invalid_argument& e) {
        cout << "Input error: " << e.what() << endl;
    } catch (...) {
        cout << "Something went wrong while adding expense!" << endl;
    }
}

// Helper to display a single expense
void display_expense(const vector<string>& data) {
    if (data.size() == 4) {
        cout << left << setw(15) << data[0]   // Date
             << setw(10) << data[1]            // Amount
             << setw(15) << data[2]            // Category
             << setw(30) << data[3] << endl;   // Description
    }
}

// Function to view all expenses
void view_expenses() {
    ifstream file(FILENAME);
    string line;
    double total = 0.0;

    if (file.is_open()) {
        cout << "\n--- All Expenses ---\n";
        cout << left << setw(15) << "Date" << setw(10) << "Amount" << setw(15) << "Category" << setw(30) << "Description" << endl;
        cout << string(70, '-') << endl;

        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> data;
            string item;
            while (getline(ss, item, ',')) {
                data.push_back(item);
            }
            if (data.size() == 4) {
                display_expense(data);
                total += stod(data[1]);
            }
        }
        cout << string(70, '-') << endl;
        cout << right << setw(55) << "Total: $" << fixed << setprecision(2) << total << endl;
        file.close();
    } else {
        cout << "❌ No expenses found.\n";
    }
}

// Function to filter expenses by category
void filter_by_category() {
    string category;
    cout << "Enter category to filter: ";
    cin.ignore();
    getline(cin, category);

    ifstream file(FILENAME);
    string line;
    double total = 0.0;

    if (file.is_open()) {
        cout << "\n--- Expenses for category: " << category << " ---\n";
        cout << left << setw(15) << "Date" << setw(10) << "Amount" << setw(15) << "Category" << setw(30) << "Description" << endl;
        cout << string(70, '-') << endl;

        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> data;
            string item;
            while (getline(ss, item, ',')) {
                data.push_back(item);
            }
            if (data.size() == 4 && to_lower(data[2]) == to_lower(category)) {
                display_expense(data);
                total += stod(data[1]);
            }
        }
        cout << string(70, '-') << endl;
        cout << right << setw(55) << "Total in " << category << ": $" << fixed << setprecision(2) << total << endl;
        file.close();
    } else {
        cout << "❌ No expenses found.\n";
    }
}

// Function to filter expenses by date
void filter_by_date() {
    string date;
    cout << "Enter date to filter (YYYY-MM-DD): ";
    cin >> date;

    ifstream file(FILENAME);
    string line;
    double total = 0.0;

    if (file.is_open()) {
        cout << "\n--- Expenses for date: " << date << " ---\n";
        cout << left << setw(15) << "Date" << setw(10) << "Amount" << setw(15) << "Category" << setw(30) << "Description" << endl;
        cout << string(70, '-') << endl;

        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> data;
            string item;
            while (getline(ss, item, ',')) {
                data.push_back(item);
            }
            if (data.size() == 4 && data[0] == date) {
                display_expense(data);
                total += stod(data[1]);
            }
        }
        cout << string(70, '-') << endl;
        cout << right << setw(55) << "Total on " << date << ": $" << fixed << setprecision(2) << total << endl;
        file.close();
    } else {
        cout << "❌ No expenses found.\n";
    }
}

// NEW Function: Show total expenses
void total_expenses() {
    ifstream file(FILENAME);
    string line;
    double total = 0.0;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> data;
            string item;
            while (getline(ss, item, ',')) {
                data.push_back(item);
            }
            if (data.size() == 4) {
                total += stod(data[1]);
            }
        }
        cout << "\n💰 Total Expenses: $" << fixed << setprecision(2) << total << endl;
        file.close();
    } else {
        cout << "❌ No expenses found.\n";
    }
}

// NEW Function: Show total expenses by category
void total_expenses_by_category() {
    ifstream file(FILENAME);
    string line;
    map<string, double> category_totals;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> data;
            string item;
            while (getline(ss, item, ',')) {
                data.push_back(item);
            }
            if (data.size() == 4) {
                string category = data[2];
                double amount = stod(data[1]);
                category_totals[category] += amount;
            }
        }

        cout << "\n💰 Total Expenses by Category:\n";
        for (const auto& entry : category_totals) {
            cout << left << setw(15) << entry.first 
                 << " : $" << fixed << setprecision(2) << entry.second << endl;
        }

        file.close();
    } else {
        cout << "❌ No expenses found.\n";
    }
}

// Main menu
void main_menu() {
    int choice;
    do {
        cout << "\n========= Expense Tracker Menu =========\n";
        cout << "1. Add Expense\n";
        cout << "2. View All Expenses\n";
        cout << "3. Filter by Category\n";
        cout << "4. Filter by Date\n";
        cout << "5. Show Total Expenses\n";
        cout << "6. Show Total Expenses by Category\n";
        cout << "7. Exit\n";
        cout << "Enter your choice (1-7): ";
        cin >> choice;

        switch (choice) {
            case 1: add_expense(); break;
            case 2: view_expenses(); break;
            case 3: filter_by_category(); break;
            case 4: filter_by_date(); break;
            case 5: total_expenses(); break;
            case 6: total_expenses_by_category(); break;
            case 7: cout << "👋 Goodbye!\n"; break;
            default: cout << "⚠️ Invalid choice! Please try again.\n"; break;
        }
    } while (choice != 7);
}

// Main function
int main() {
    main_menu();
    return 0;
}
