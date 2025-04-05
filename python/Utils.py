from datetime import datetime

CATEGORIES = ["Food", "Transport", "Shopping", "Entertainment", "Utilities", "Healthcare", "Other"]

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

def getvalidCategory():
    print("📋 Available Categories:")
    for idx, cat in enumerate(CATEGORIES, start=1):
        print(f" {idx}. {cat}")

    # Convert all the categories to lower case for proper comparision
    valid_categories = [cat.lower() for cat in CATEGORIES]

    while True:
        selected = input("Choose a category: ").strip().lower()
        if selected in valid_categories:
            return CATEGORIES[valid_categories.index(selected)]
        else:
            print("❌ Invalid category. Please choose from the list above.")  