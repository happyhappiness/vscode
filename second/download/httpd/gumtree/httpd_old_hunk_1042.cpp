
/*************************************************
*       Functions for directory scanning         *
*************************************************/

/* These functions are defined so that they can be made system specific,
although at present the only ones are for Unix, and for "no directory recursion
support". */


/************* Directory scanning in Unix ***********/

#if IS_UNIX
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

typedef DIR directory_type;

int
isdirectory(char *filename)
{
struct stat statbuf;
if (stat(filename, &statbuf) < 0)
  return 0;        /* In the expectation that opening as a file will fail */
return ((statbuf.st_mode & S_IFMT) == S_IFDIR)? '/' : 0;
}

directory_type *
opendirectory(char *filename)
{
return opendir(filename);
}

char *
readdirectory(directory_type *dir)
{
for (;;)
  {
  struct dirent *dent = readdir(dir);
  if (dent == NULL) return NULL;
  if (strcmp(dent->d_name, ".") != 0 && strcmp(dent->d_name, "..") != 0)
    return dent->d_name;
  }
return NULL;   /* Keep compiler happy; never executed */
}

void
closedirectory(directory_type *dir)
{
closedir(dir);
}


#else


/************* Directory scanning when we can't do it ***********/

/* The type is void, and apart from isdirectory(), the functions do nothing. */

typedef void directory_type;

int isdirectory(char *filename) { return FALSE; }
directory_type * opendirectory(char *filename) {}
char *readdirectory(directory_type *dir) {}
void closedirectory(directory_type *dir) {}
