import csv
import os
from datetime import datetime

FILE_NAME = 'expensesDatabase.csv'
FIELDNAMES = ['date', 'amount', 'category', 'description']

def getValidDate():
    while True:
        date = input("Enter date (YYYY-MM-DD): ").strip()
        try:
            entered_date = datetime.strptime(date, "%Y-%m-%d").date()
            today = datetime.today().date()
            if entered_date < today:
                print("You cannot add past dates. Please try again!")
                continue
            return date
        except ValueError:
            print("Invalid date format. Please enter in YYYY-MM-DD format again! ")
            continue

def add_expense():
    date = getValidDate()
    amount = float(input("Enter amount: "))
    category = input("Enter category: ").strip()
    description = input("Enter description: ").strip()

    with open(FILE_NAME, mode='a', newline='') as file:
        writer = csv.DictWriter(file, fieldnames=['date', 'amount', 'category', 'description'])
        if not os.path.isfile(FILE_NAME) or os.stat(FILE_NAME).st_size == 0:
            writer.writeheader()
        writer.writerow({'date': date, 'amount': amount, 'category': category, 'description': description})
    print("Expense added successfully!\n")


def view_expenses():
    if not os.path.isfile(FILE_NAME) or os.stat(FILE_NAME).st_size == 0:
        print("No expenses found.")
        return []

    with open(FILE_NAME, mode='r', newline='') as file:
        reader = csv.DictReader(file)
        expenses = list(reader)

    print("Expense Records:")
    for idx, expense in enumerate(expenses, start=1):
        
        print(f"{idx}. Date: {expense['date']}, Amount: {expense['amount']}, "
              f"Category: {expense['category']}, Description: {expense['description']}")
    
    return expenses

def filter_by_category():
    target_category = input("Enter category to filter: ")
    if not os.path.isfile(FILE_NAME) or os.stat(FILE_NAME).st_size == 0:
        print("No expenses found.")
        return []

    with open(FILE_NAME, mode='r', newline='') as file:
        reader = csv.DictReader(file)
        reader.fieldnames = [name.strip().lower() for name in reader.fieldnames]
        expenses = [row for row in reader if row['category'].lower() == target_category.lower()]

    if not expenses:
        print(f" No expenses found for category: {target_category}")
    else:
        print(f" Expenses in category '{target_category}':")
        for idx, expense in enumerate(expenses, start=1):
            print(f"{idx}. Date: {expense['date']}, Amount: {expense['amount']}, "
                  f"Category: {expense['category']}, Description: {expense['description']}")
    
    return expenses

def filter_by_date():
    target_date = getValidDate()

    if not os.path.isfile(FILE_NAME) or os.stat(FILE_NAME).st_size == 0:
        print("No expenses found.")
        return []

    with open(FILE_NAME, mode='r', newline='') as file:
        reader = csv.DictReader(file)
        reader.fieldnames = [name.strip().lower() for name in reader.fieldnames]
        expenses = [row for row in reader if row['date'].strip() == target_date]

    if not expenses:
        print(f"No expenses found for date: {target_date}")
    else:
        print(f"Expenses on '{target_date}':")
        for idx, expense in enumerate(expenses, start=1):
            print(f"{idx}. Date: {expense['date']}, Amount: {expense['amount']}, "
                  f"Category: {expense['category']}, Description: {expense['description']}")
    
    return expenses

def calculate_total_expense():
    if not os.path.isfile(FILE_NAME) or os.stat(FILE_NAME).st_size == 0:
        print("📂 No expenses found.")
        return 0.0

    total = 0.0

    with open(FILE_NAME, mode='r', newline='') as file:
        reader = csv.DictReader(file)
        reader.fieldnames = [name.strip().lower() for name in reader.fieldnames]

        for row in reader:
            try:
                amount = float(row['amount'])
                total += amount
            except (ValueError, KeyError):
                print(f"⚠️ Skipping invalid row: {row}")

    print(f"💰 Total Expense: ${total:.2f}")
    return total

from collections import defaultdict

def sum_expenses_by_category():
    if not os.path.isfile(FILE_NAME) or os.stat(FILE_NAME).st_size == 0:
        print(" No expenses found.")
        return {}

    category_totals = defaultdict(float)

    with open(FILE_NAME, mode='r', newline='') as file:
        reader = csv.DictReader(file)
        reader.fieldnames = [name.strip().lower() for name in reader.fieldnames]

        for row in reader:
            try:
                category = row['category'].strip().lower()
                amount = float(row['amount'])
                category_totals[category] += amount
            except (ValueError, KeyError):
                print(f"⚠️ Skipping invalid row: {row}")

    if not category_totals:
        print("🔍 No valid expenses found.")
    else:
        print("📊 Total Expenses by Category:")
        for category, total in category_totals.items():
            print(f" - {category.capitalize()}: ${total:.2f}")

    return dict(category_totals)

    