#include "file.h"

typedef struct project {
	char name[256];
	File files[128];
	int file_count;
} Project;

void print_project(Project *p);
void gen_makefile(Project *p);
Project new_project();
