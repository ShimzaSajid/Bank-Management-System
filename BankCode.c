// Simple Banking System
// Built in C | By Shimza Sajid
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // for getch()

struct acc_detail {
    char acc_num[20];
    char name[50];
    char password[10];
    float balance;
};

// Function to hide password input with asterisks
void getPassword(char *password) {
    char ch;
    int i = 0;

    while (1) {
        ch = getch();
        if (ch == 13) { // Enter key
            password[i] = '\0';
            printf("\n");
            break;
        } else if (ch == 8) { // Backspace
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (i < 9) { // Max length 9 + 1 for \0
            password[i++] = ch;
            printf("*");
        }
    }
}

// Function to log transactions
void log_transaction(const char *acc_num, const char *action, float amount, const char *target_acc) {
    char historyFile[50];
    FILE *fp;
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    sprintf(historyFile, "%s_history.txt", acc_num);
    fp = fopen(historyFile, "a");

    if (fp != NULL) {
        fprintf(fp, "[%02d-%02d-%04d %02d:%02d:%02d] ",
                t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
                t->tm_hour, t->tm_min, t->tm_sec);

        if (strcmp(action, "Transfer Sent") == 0 || strcmp(action, "Transfer Received") == 0) {
            fprintf(fp, "%s: Rs %.2f %s %s\n", action, amount,
                    strcmp(action, "Transfer Sent") == 0 ? "to" : "from", target_acc);
        } else {
            fprintf(fp, "%s: Rs %.2f\n", action, amount);
        }

        fclose(fp);
    }
}

int main() {
    struct acc_detail user, user1;
    int choice, main_choice;
    FILE *fp;
    char fileName[30];
    char enter_acc[30], enter_pass[10];
    float amount;

    while (1) {
        system("cls");
        printf("\n=======================================");
        printf("\n     Welcome to Simple Banking ");
        printf("\n=======================================\n");
        printf("1.  Create an Account\n");
        printf("2.  Login to an Account\n");
        printf("3.  Exit\n");
        printf("---------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &main_choice);

        if (main_choice == 1) {
            system("cls");
            printf("\n--- Create a New Account ---\n");
            printf("Enter the account number: ");
            scanf("%s", user.acc_num);
            printf("Enter your name: ");
            scanf("%s", user.name);
            printf("Create your password: ");
            getPassword(user.password);
            user.balance = 0;

            strcpy(fileName, user.acc_num);
            strcat(fileName, ".dat");
            fp = fopen(fileName, "w");

            if (fp != NULL) {
                fwrite(&user, sizeof(struct acc_detail), 1, fp);
                fclose(fp);

                char historyFile[50];
                sprintf(historyFile, "%s_history.txt", user.acc_num);
                fp = fopen(historyFile, "w");
                if (fp != NULL) fclose(fp);

                printf("\n Account successfully created!\n");
            } else {
                printf(" Error! Could not create account.\n");
            }

            printf("\nPress Enter to continue...");
            getchar(); getchar();
        }

        else if (main_choice == 2) {
            system("cls");
            printf("\n--- Login to Your Account ---\n");
            printf("Enter account number: ");
            scanf("%s", enter_acc);
            printf("Enter password: ");
            getPassword(enter_pass);

            strcpy(fileName, enter_acc);
            strcat(fileName, ".dat");
            fp = fopen(fileName, "r");

            if (fp == NULL) {
                printf("\n Account not found.\n");
                printf("\nPress Enter to continue...");
                getchar(); getchar();
                continue;
            }

            fread(&user, sizeof(struct acc_detail), 1, fp);
            fclose(fp);

            if (!strcmp(enter_pass, user.password)) {
                do {
                    system("cls");
                    printf("\n=======================================\n");
                    printf("   Logged In as: %s\n", user.name);
                    printf("=======================================\n");
                    printf("1.  Check Balance\n");
                    printf("2.  Deposit Money\n");
                    printf("3.  Transfer Money\n");
                    printf("4.  Withdraw Money\n");
                    printf("5.  Transaction History\n");
                    printf("6.  Account Details\n");
                    printf("7.  Logout\n");
                    printf("---------------------------------------\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            printf("\n Your current balance: Rs. %.2f\n", user.balance);
                            break;

                        case 2:
                            printf("\nEnter deposit amount: Rs. ");
                            scanf("%f", &amount);
                            user.balance += amount;
                            fp = fopen(fileName, "w");
                            if (fp != NULL) {
                                fwrite(&user, sizeof(struct acc_detail), 1, fp);
                                fclose(fp);
                                log_transaction(user.acc_num, "Deposit", amount, NULL);
                                printf(" Rs. %.2f deposited successfully!\n", amount);
                            } else {
                                printf(" File error.\n");
                            }
                            break;

                        case 3:
                            printf("\nEnter recipient account number: ");
                            scanf("%s", enter_acc);
                            printf("Enter amount to transfer: Rs. ");
                            scanf("%f", &amount);

                            char targetFile[30];
                            strcpy(targetFile, enter_acc);
                            strcat(targetFile, ".dat");

                            fp = fopen(targetFile, "r");
                            if (fp == NULL) {
                                printf(" Account not found.\n");
                                break;
                            }

                            fread(&user1, sizeof(struct acc_detail), 1, fp);
                            fclose(fp);

                            if (amount > user.balance) {
                                printf(" Insufficient balance!\n");
                            } else {
                                user1.balance += amount;
                                fp = fopen(targetFile, "w");
                                fwrite(&user1, sizeof(struct acc_detail), 1, fp);
                                fclose(fp);
                                log_transaction(user1.acc_num, "Transfer Received", amount, user.acc_num);

                                user.balance -= amount;
                                fp = fopen(fileName, "w");
                                fwrite(&user, sizeof(struct acc_detail), 1, fp);
                                fclose(fp);
                                log_transaction(user.acc_num, "Transfer Sent", amount, enter_acc);

                                printf(" Rs. %.2f transferred to %s\n", amount, enter_acc);
                            }
                            break;

                        case 4:
                            printf("\nEnter withdrawal amount: Rs. ");
                            scanf("%f", &amount);
                            if (amount > user.balance) {
                                printf(" Insufficient balance!\n");
                            } else {
                                user.balance -= amount;
                                fp = fopen(fileName, "w");
                                fwrite(&user, sizeof(struct acc_detail), 1, fp);
                                fclose(fp);
                                log_transaction(user.acc_num, "Withdrawal", amount, NULL);
                                printf(" Rs. %.2f withdrawn successfully!\n", amount);
                            }
                            break;

                        case 5: {
                            char historyFile[50];
                            sprintf(historyFile, "%s_history.txt", user.acc_num);
                            fp = fopen(historyFile, "r");
                            if (fp != NULL) {
                                char line[200];
                                printf("\n--- Transaction History ---\n");
                                while (fgets(line, sizeof(line), fp)) {
                                    printf("%s", line);
                                }
                                fclose(fp);
                            } else {
                                printf(" No transaction history found.\n");
                            }
                            break;
                        }

                        case 6:
                            printf("\n--- Account Details ---\n");
                            printf("Account Number: %s\n", user.acc_num);
                            printf("Name          : %s\n", user.name);
                            printf("Balance       : Rs. %.2f\n", user.balance);
                            break;

                        case 7:
                            printf("\n Logging out...\n");
                            break;

                        default:
                            printf(" Invalid choice.\n");
                            break;
                    }

                    printf("\nPress Enter to continue...");
                    getchar(); getchar();
                } while (choice != 7);
            } else {
                printf("\n Invalid password.\n");
                printf("\nPress Enter to continue...");
                getchar(); getchar();
            }
        }

        else if (main_choice == 3) {
            printf("\n Exiting the program. Thank you!\n");
            break;
        }

        else {
            printf("\n Invalid choice! Please try again.\n");
            printf("Press Enter to continue...");
            getchar(); getchar();
        }
    }

    return 0;
}
