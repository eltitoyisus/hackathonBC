#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <xlsxwriter.h>

void create_user(const char* username, double userTokens) {
    lxw_workbook  *workbook = workbook_new("users_data.xlsx");
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);

    worksheet_write_string(worksheet, 0, 0, "Username", NULL);
    worksheet_write_string(worksheet, 0, 1, "Tokens Earned", NULL);

    worksheet_write_string(worksheet, 1, 0, username, NULL);
    worksheet_write_number(worksheet, 1, 1, userTokens, NULL);

    workbook_close(workbook);
}

void append_user(const char* username, double userTokens) {
    lxw_workbook  *workbook = workbook_open("users_data.xlsx");
    lxw_worksheet *worksheet = workbook_get_worksheet_by_name(workbook, "Sheet1");

    int row = worksheet_row_count(worksheet);

    worksheet_write_string(worksheet, row, 0, username, NULL);
    worksheet_write_number(worksheet, row, 1, userTokens, NULL);

    workbook_close(workbook);
}

void handle_create_user(const char* username, double userTokens) {
    if (access("users_data.xlsx", F_OK) == -1) {
        create_user(username, userTokens);
    } else {
        append_user(username, userTokens);
    }
}

int main() {
    const char* username = "user123";
    double userTokens = 100;

    handle_create_user(username, userTokens);

    printf("User created and saved to Excel file successfully.\n");

    return 0;
}
