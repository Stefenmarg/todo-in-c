//
// Created by stefenmarg on 8/02/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void spacer(const char* command, const char* description);
void removeNewLines(char *str);

void add(int argc, char *argv[], FILE *database) {
	if (argc == 2) {
		printf("No task description provided. Skipping\n");
		return;
	}
	to_do Entry;

	removeNewLines(argv[argc-1]);
	for (int i=2; i <argc; i++) {
		strcat(Entry.task, argv[i]);
		strcat(Entry.task, " ");
	}
	printf("Added task: %s\n", Entry.task);
	Entry.status = STATUS_PENDING;

	fwrite(&Entry, sizeof(to_do), 1, database);

	fflush(database);
}

void list(FILE *database) {
	fseek(database, 0, SEEK_SET);
	
	to_do Entry;

	int total_entries = 0;
	int total_pending_entries = 0;
	int total_complete_entries = 0;
	while (fread(&Entry, sizeof(to_do), 1, database) == 1) {
		if (Entry.status != STATUS_DELETED) {
			if (Entry.status == STATUS_PENDING) {
				total_pending_entries++;
				printf("[%d] [Status: Pending] -- %s\n", total_pending_entries, Entry.task);
			} 			
			if (Entry.status == STATUS_COMPLETE) {
				total_complete_entries++;
				printf("[X] [Status: Complete] -- %s\n", Entry.task);

			}
			total_entries++;
		}
		
	}
	
	if (!total_pending_entries) {
		printf("Your to-do list is currently empty. Try adding some stuff!\n");
		return;
	}


	if (total_complete_entries) {
		double percent_complete = 100.0 * (double)total_complete_entries / total_entries;
		printf("Percentage complete: %.2f%%\n", percent_complete);
	}
}

void done(int argc, char *argv[], FILE *database) {
	if (argc == 2) {
		printf("No task id provided. Skipping\n");
		return;
	}

	int success_flag=0;
	int pending_ids=0;
	int done_id = atoi(argv[2]);

	to_do Entry;

	fseek(database, 0, SEEK_SET);
	while (fread(&Entry, sizeof(to_do), 1, database) == 1) {
		if (Entry.status == STATUS_PENDING) {
			pending_ids++;
			if (pending_ids == done_id) {
				fseek(database, -1 * sizeof(to_do), SEEK_CUR);
				Entry.status = STATUS_COMPLETE;
				fwrite(&Entry, sizeof(to_do), 1, database);
				success_flag++;
			}

		}
	}

	if (!success_flag) {
		printf("There wasnt an entry with the id: %d\n", done_id);
	} else {
		printf("Congrats! Another to-do element completed!\n");
	}
}

void purge(int argc, char *argv[], FILE *database) {
	if (argc == 2) {
		printf("No task id provided. Skipping\n");
		return;
	}

	int success_flag=0;
	int pending_ids=0;
	int done_id = atoi(argv[2]);

	to_do Entry;

	fseek(database, 0, SEEK_SET);
	while (fread(&Entry, sizeof(to_do), 1, database) == 1) {
		if (Entry.status == STATUS_PENDING) {
			pending_ids++;
			if (pending_ids == done_id) {
				fseek(database, -1 * sizeof(to_do), SEEK_CUR);
				Entry.status = STATUS_DELETED;
				fwrite(&Entry, sizeof(to_do), 1, database);
				success_flag++;
			}

		}
	}

	if (!success_flag) {
		printf("There wasnt an entry with the id: %d\n", done_id);
	} else {
		printf("to-do entry removed successfully\n");
	}
}


void help(void) {
    printf("todo: A simple CLI todo program written in C\n");
    printf("Usage: todo <command> [option(s)] [arg(s)]\n\n");

    printf("Commands:\n");
    spacer("add <task>", "Adds a task to the list");
    spacer("list", "Lists all pending todo tasks");
    spacer("done <id>", "Marks the task as done");
    spacer("purge <id>", "Removes the task");
    spacer("edit <id> <task>", "Edits task content");
    spacer("clear", "Removes completed tasks");
    spacer("help", "Shows the help message");

    printf("\nOptions:\n");
    spacer("-h, --help", "Shows the help message");
}