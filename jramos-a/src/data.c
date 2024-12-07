#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <xlsxwriter.h>

// Function to create a new user and store it in an Excel file
void create_user(const char* username, double userTokens) {
    // Open or create an Excel workbook
    lxw_workbook  *workbook = workbook_new("users_data.xlsx");
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);

    // Add a header row to the Excel file (if it's the first time creating the file)
    worksheet_write_string(worksheet, 0, 0, "Username", NULL);
    worksheet_write_string(worksheet, 0, 1, "Tokens Earned", NULL);

    // Write the user data to the next row
    worksheet_write_string(worksheet, 1, 0, username, NULL);
    worksheet_write_number(worksheet, 1, 1, userTokens, NULL);

    // Close the workbook to save the changes
    workbook_close(workbook);
}

// Function to append user data to an existing Excel file
void append_user(const char* username, double userTokens) {
    // Open an existing Excel file
    lxw_workbook  *workbook = workbook_open("users_data.xlsx");
    lxw_worksheet *worksheet = workbook_get_worksheet_by_name(workbook, "Sheet1");

    // Find the next available row
    int row = worksheet_row_count(worksheet);

    // Write the user data to the next available row
    worksheet_write_string(worksheet, row, 0, username, NULL);
    worksheet_write_number(worksheet, row, 1, userTokens, NULL);

    // Close the workbook to save the changes
    workbook_close(workbook);
}

// Example: Function to create and append user (if no file exists)
void handle_create_user(const char* username, double userTokens) {
    // Check if the file exists, if not, create and add data to it
    if (access("users_data.xlsx", F_OK) == -1) {
        create_user(username, userTokens);
    } else {
        append_user(username, userTokens);
    }
}

int main() {
    // Example: Create a new user with auto-generated username
    const char* username = "user123";  // This can be dynamically generated
    double userTokens = 100;  // This will be dynamically updated in your app

    handle_create_user(username, userTokens);

    printf("User created and saved to Excel file successfully.\n");

    return 0;
}
