#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "project.h"

int fexists(char *filename) {
	struct stat buffer;
	return stat(filename, &buffer);
}

void print_project(Project *p) {
	for (int i = 0; i < p->file_count; i++)
		print_file(&p->files[i]);
}

void gen_makefile(Project *p) {
	char *filename;
	
	// find an available filename
	if (fexists("Makefile")) {
		printf("Makefile does not exist yet, writing\n\n");
		filename = "Makefile";
	} else {
		for (int i = 1;; i++) {
			char altname[32];
			sprintf(altname, "Makefile%d", i);
			if (fexists(altname)) {
				printf("%s does not exist yet, writing\n\n", altname);
				filename = strdup(altname);
				break;
			}
		}
	}
	
	printf("Creating file");
	
	FILE *fp = fopen(filename, "w");
	
	// write makefile
	fprintf(fp, "CC=clang\n");
	fprintf(fp, "CFLAGS=-I.\n");
	fprintf(fp, "DEPS=");
	
	for (int i = 0; i < p->file_count; i++)
		if (p->files[i].type == Header)
			fprintf(fp, "%s%s ", p->files[i].dir, p->files[i].name);
	
	fprintf(fp, "\nSOURCES=");

	for (int i = 0; i < p->file_count; i++)
		if (p->files[i].type == Source)
			fprintf(fp, "%s%s ", p->files[i].dir, p->files[i].name);
	
	fprintf(fp, "\n\n%%.o: %%.c $(DEPS)\n\t$(CC) -g -c -o $@ $< $(CFLAGS)\n\n");
	fprintf(fp, "\n\nmkgen: $(SOURCES)\n\t$(CC) -g -o a.out $(SOURCES)");
	
	printf("Makefile created.\n");
	fclose(fp);
	
	// return;
}

void crawl_files(Project *p, char *dir) {
	DIR *d;
	struct dirent *ent;
	d = opendir(dir);
	if (d) {
		while((ent = readdir(d)) != NULL) {
			File f = new_file(ent, dir);
			
			if (f.type == Dir) {
				// do not crawl hidden dirs
				if (f.name[0] != '.') {
					char newdir[256];
					sprintf(newdir, "%s%s/", dir, f.name);
					// printf("formatted: %s\n", newdir);
					// crawl_files(p, f.name);
					crawl_files(p, newdir);
				}
			} else {
				memcpy(&p->files[p->file_count], &f, sizeof(f));
				p->file_count++;
			}
		}
		closedir(d);
	}
}

Project new_project() {
	Project p;
	p.file_count = 0;
	crawl_files(&p, "./");
	return p;
}
