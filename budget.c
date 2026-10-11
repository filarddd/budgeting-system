#include <stdio.h>
#include <string.h>

#define MAX_TRANSACTIONS 1000
#define DATE 11
#define CATEGORY 30

char dates[MAX_TRANSACTIONS][DATE];
char categories[MAX_TRANSACTIONS][CATEGORY];
float amounts[MAX_TRANSACTIONS];
int incomes[MAX_TRANSACTIONS];

int transCount = 0;

void addTrans() {
    if (transCount >= MAX_TRANSACTIONS) {
        printf("Transaction limit reached.\n");
        return;
    }

    printf("Enter date (YYYY-MM-DD): ");
    scanf("%10s", *(dates + transCount));

    printf("Enter Category: ");
    scanf("%29s", *(categories + transCount));

    printf("Enter amount: ");
    scanf("%f", *(amounts + transCount));

    printf("Is this Income? (1 for YES, 0 for NO): ");
    scanf("%d", *(incomes + transCount));

    transCount++;
    printf("Transaction added successfully.\n");
}

void summary() {
    float income = 0.0f, expense_total = 0.0f;
    int *income_ptr = incomes;
    float *amount_ptr = amounts;

    for (int i = 0; i < transCount; i++) {
        if (*(income_ptr + i) == 1) {
            income += *(amount_ptr + i);
        } else {
            expense_total += *(amount_ptr + i);
        }
    }

    printf("\nSummary:\n");
    printf("Total Income: %.2f\n", income);
    printf("Total Expense: %.2f\n", expense_total);
    printf("Balance: %.2f\n", income - expense_total);
}

void view() {
    char period[DATE];
    float net_total = 0.0f;
    char (*date_ptr)[DATE] = dates;
    char (*category_ptr)[CATEGORY] = categories;
    float *amount_ptr = amounts;
    int *income_ptr = incomes;

    printf("Enter the period (YYYY-MM-DD or YYYY-MM): ");
    scanf("%10s", period);

    printf("\nTransactions for period: %s\n", period);

    for (int i = 0; i < transCount; i++) {
        if (strncmp(*(date_ptr + i), period, strlen(period)) == 0) {
            printf("Date: %s | Category: %s | Amount: %.2f | Type: %s\n",
                   *(date_ptr + i),
                   *(category_ptr + i),
                   *(amount_ptr + i),
                   (*(income_ptr + i) == 1) ? "Income" : "Expense");
            if (*(income_ptr + i) == 1) {
                net_total += *(amount_ptr + i);
            } else {
                net_total -= *(amount_ptr + i);
            }
        }
    }
    printf("Net Total for period %s: %.2f\n", period, net_total);
}

void save() {
    FILE *file = fopen("transactions.txt", "w");
    char (*date_ptr)[DATE] = dates;
    char (*category_ptr)[CATEGORY] = categories;
    float *amount_ptr = amounts;
    int *income_ptr = incomes;

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < transCount; i++) {
        fprintf(file, "%s,%s,%.2f,%d\n",
                *(date_ptr + i),
                *(category_ptr + i),
                *(amount_ptr + i),
                *(income_ptr + i));
    }
    fclose(file);
    printf("Transactions saved successfully.\n");
}

void load() {
    FILE *file = fopen("transactions.txt", "r");
    if (file == NULL) {
        printf("No saved transactions found.\n");
        return;
    }

    transCount = 0;
    while (fscanf(file, "%10s %29s %f %d\n",
                  *(dates + transCount),
                  *(categories + transCount),
                  (amounts + transCount),
                  (incomes + transCount)) == 4) {
        transCount++;
        if (transCount >= MAX_TRANSACTIONS) {
            printf("Transaction limit reached while loading.\n");
            break;
        }
    }
    fclose(file);
    printf("Transactions loaded successfully.\n");
}

void menu() {
    int choice = -1;
    
    while (choice != 0) {
        printf("\nBudget Management System\n");
        printf("1. Add Transaction\n");
        printf("2. View Transactions\n");
        printf("3. Summary\n");
        printf("4. Save Transactions\n");
        printf("5. Load Transactions\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            addTrans();
        } else if (choice == 2) {
            view();
        } else if (choice == 3) {
            summary();
        } else if (choice == 4) {
            save();
        } else if (choice == 5) {
            load();
        } else if (choice == 0) {
            printf("Exiting...\n");
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
}

int main() {
    load();
    menu();
    return 0;
}