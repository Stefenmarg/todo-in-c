//
// Created by stefenmarg on 8/02/25.
//
#include <stdio.h>
#include <string.h>

void spacer(const char* command, const char* description);
void removeNewLines(char *str);

void add(int argc, char *argv[], FILE *database) {
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
	int total_complete_entries = 0;
	while (fread(&Entry, sizeof(to_do), 1, database) == 1) {
		total_entries++;
		if (Entry.status != STATUS_DELETED) {
			if (Entry.status == STATUS_COMPLETE) total_complete_entries++;
			printf("[%d] [Status: %s] -- %s\n", total_entries, Entry.status ? "Complete" : "Pending", Entry.task);
		}
	}
	
	if (!total_entries) {
		printf("Your to-do list is currently empty. Try adding some stuff!\n");
		return;
	}


	if (total_complete_entries) {
		printf("Percentage complete: %.2f \n", (float)(total_entries - total_complete_entries)/total_entries);
	}
}

void help(void) {
    printf("todo: A simple CLI todo program written in C\n");
    printf("Usage: todo <command> [option(s)] [arg(s)]\n\n");

    printf("Commands:\n");
    spacer("add <task>", "Adds a task to the list");
    spacer("list", "Lists all todo tasks");
    spacer("done <id>", "Marks the task as done");
    spacer("remove <id>", "Removes the task");
    spacer("edit <id> <task>", "Edits task content");
    spacer("clear", "Removes completed tasks");
    spacer("help", "Shows the help message");

    printf("\nOptions:\n");
    spacer("-h, --help", "Shows the help message");
}