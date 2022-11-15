#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

// #include "file.h"
#include "project.h"

int main() {
	Project p = new_project();
	gen_makefile(&p);
	return 0;
}


