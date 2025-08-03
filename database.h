//
// Created by stefenmarg on 7/29/25.
//

#ifndef DATABASE_H
#define DATABASE_H

#endif //DATABASE_H

#include <stdio.h>
#include <stdlib.h>

FILE* load_database(void) {
    FILE *DATABASE_FILE = fopen(DATABASE_PATH, "rb+");
    if (DATABASE_FILE == NULL) {
        printf("Database not found; creating one.");
        DATABASE_FILE = fopen(DATABASE_PATH, "ab+");
    }
    fseek(DATABASE_FILE, 0, SEEK_END);
    return DATABASE_FILE;
}