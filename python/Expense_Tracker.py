from datetime import datetime
import Operation

# Main Menu
def main_menu():
    while True:
        print("\n--- Expense Tracker Menu ---")
        print("1. Add Expense")
        print("2. View Expenses")
        print("3. Filter by Category")
        print("4. Filter by Date")
        print("5. Show Total Expenses")
        print("6. Show Total Expenses by Category")
        print("7. Exit")
        choice = input("Enter your choice (1-7): ")

        if choice == '1':
            Operation.add_expense()
        elif choice == '2':
            Operation.view_expenses()
        elif choice == '3':
            Operation.filter_by_category()
        elif choice == '4':
            Operation.filter_by_date()
        elif choice == '5':
            Operation.calculate_total_expense()
        elif choice == '6':
            Operation.sum_expenses_by_category()
        elif choice == '7':
            print("Exiting... Goodbye!")
            break
        else:
            print("Invalid choice! Please try again.")

# Run the app
if __name__ == "__main__":
    main_menu()
