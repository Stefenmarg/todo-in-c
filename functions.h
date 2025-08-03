//
// Created by stefenmarg on 8/02/25.
//
#include <stdio.h>

// The indent that the command will have from the start of the terminal
#define INDENT_LEN 2
// The space between the command and it's explanation
#define SPACE_LEN 24

// A command to easily print the commands and options of the CLI
void spacer(const char* command, const char* description) {
    printf("%*s%-*s%s\n", INDENT_LEN, "", SPACE_LEN, command, description);
}

// Remove the new line character at the end of strings 
void removeNewLines(char *str) {
	char *src = str, *dst = str;
	while(*src != '\0') {
		if (*src != '\n') {
			*dst = *src;
			dst++;
		}
		src++;
	}
	*dst = '\0';
}