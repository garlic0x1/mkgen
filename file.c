#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "file.h"

void print_file(File *f) {
	printf("FILE:\n\tname: %s%s\n\ttype: %d\n", f->dir, f->name, f->type);
}

File new_file(struct dirent *ent, char *dir) {
	File f;
	f.name = strdup(ent->d_name);
	f.dir = strdup(dir);

		size_t len;
	char extension[4];
	// manually add string terminator
	memset(extension, '\0', sizeof(extension));
	
	switch (ent->d_type) {
	case DT_DIR :
		f.type = Dir;
		break;
	case DT_REG :
		// decide if source or header based on extension
		// if filename isnt longer than 2 its Other
		len = strlen(f.name );
		if (len > 2) {
			strcpy(extension, &f.name [len - 2]);
			if (!strcmp(extension, ".h")) {
				f.type = Header;
				break;
			}
			if (!strcmp(extension, ".c")) {
				f.type = Source;
				break;
			}
		}
	default :
		f.type = Other;
	}
	
	return f;
}
