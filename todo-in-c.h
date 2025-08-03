//
// Created by stefenmarg on 7/29/25.
//

#ifndef TODO_IN_C_H
#define TODO_IN_C_H

#define DATABASE_PATH "database.dat"
#define DATABASE_BACKUP_PATH "database.dat.bak"

// How long is the task
#define DESCRIPTION_LEN 256

// Status codes for the to-do entries
#define STATUS_PENDING 0
#define STATUS_COMPLETE 1
#define STATUS_DELETED 2

// A to-do entry
typedef struct TO_DO_ENTRY {
    char task[DESCRIPTION_LEN];
 	unsigned short int status;
} to_do;

#endif