//
// Created by stefenmarg on 7/29/25.
//
#define TODO

#include "todo-in-c.h"
#include "commands.h"
#include "database.h"
#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Showing the help page
    if (argc == 1 || (strcmp(argv[1], "--help") == 0) || (strcmp(argv[1], "-h") == 0)|| (strcmp(argv[1], "help") == 0)) {
        help();
        return 0;
    } 

    FILE *DATABASE = load_database();

    if (strcmp(argv[1], "add") == 0) {
    	add(argc, argv, DATABASE);
    } else if (strcmp(argv[1], "list") == 0) {
        list(DATABASE);
    } else if (strcmp(argv[1], "done") == 0) {
        printf("done\n");
    } else if (strcmp(argv[1], "remove") == 0) {
        printf("remove\n");
    } else if (strcmp(argv[1], "edit") == 0) {
        printf("edit\n");
    } else if (strcmp(argv[1], "clear") == 0) {
        printf("clear\n");
    } else {
    	printf("Invalid option: \'%s\'\n", argv[1]);
        help();
    }

    fclose(DATABASE);

    return 0;
}