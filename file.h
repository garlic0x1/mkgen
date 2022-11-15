#include <dirent.h>

typedef enum file_type {
	Source,
	Header,
	Dir,
	Other,
} FileType;

typedef struct file {
	char* name;
	char* dir;
	FileType type;
} File;

void print_file(File *f);
File new_file(struct dirent *ent, char *dir);
