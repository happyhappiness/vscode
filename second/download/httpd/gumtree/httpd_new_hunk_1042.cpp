
/*************************************************
*       Functions for directory scanning         *
*************************************************/

/* These functions are defined so that they can be made system specific,
although at present the only ones are for Unix, Win32, and for "no directory
recursion support". */


/************* Directory scanning in Unix ***********/

#if IS_UNIX
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

typedef DIR directory_type;

static int
isdirectory(char *filename)
{
struct stat statbuf;
if (stat(filename, &statbuf) < 0)
  return 0;        /* In the expectation that opening as a file will fail */
return ((statbuf.st_mode & S_IFMT) == S_IFDIR)? '/' : 0;
}

static directory_type *
opendirectory(char *filename)
{
return opendir(filename);
}

static char *
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

static void
closedirectory(directory_type *dir)
{
closedir(dir);
}


/************* Directory scanning in Win32 ***********/

/* I (Philip Hazel) have no means of testing this code. It was contributed by
Lionel Fourquaux. */


#elif HAVE_WIN32API

#ifndef STRICT
# define STRICT
#endif
#ifndef WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

typedef struct directory_type
{
HANDLE handle;
BOOL first;
WIN32_FIND_DATA data;
} directory_type;

int
isdirectory(char *filename)
{
DWORD attr = GetFileAttributes(filename);
if (attr == INVALID_FILE_ATTRIBUTES)
  return 0;
return ((attr & FILE_ATTRIBUTE_DIRECTORY) != 0) ? '/' : 0;
}

directory_type *
opendirectory(char *filename)
{
size_t len;
char *pattern;
directory_type *dir;
DWORD err;
len = strlen(filename);
pattern = (char *) malloc(len + 3);
dir = (directory_type *) malloc(sizeof(*dir));
if ((pattern == NULL) || (dir == NULL))
  {
  fprintf(stderr, "pcregrep: malloc failed\n");
  exit(2);
  }
memcpy(pattern, filename, len);
memcpy(&(pattern[len]), "\\*", 3);
dir->handle = FindFirstFile(pattern, &(dir->data));
if (dir->handle != INVALID_HANDLE_VALUE)
  {
  free(pattern);
  dir->first = TRUE;
  return dir;
  }
err = GetLastError();
free(pattern);
free(dir);
errno = (err == ERROR_ACCESS_DENIED) ? EACCES : ENOENT;
return NULL;
}

char *
readdirectory(directory_type *dir)
{
for (;;)
  {
  if (!dir->first)
    {
    if (!FindNextFile(dir->handle, &(dir->data)))
      return NULL;
    }
  else
    {
    dir->first = FALSE;
    }
  if (strcmp(dir->data.cFileName, ".") != 0 && strcmp(dir->data.cFileName, "..") != 0)
    return dir->data.cFileName;
  }
#ifndef _MSC_VER
return NULL;   /* Keep compiler happy; never executed */
#endif
}

void
closedirectory(directory_type *dir)
{
FindClose(dir->handle);
free(dir);
}


/************* Directory scanning when we can't do it ***********/

/* The type is void, and apart from isdirectory(), the functions do nothing. */

#else

typedef void directory_type;

int isdirectory(char *filename) { return FALSE; }
directory_type * opendirectory(char *filename) {}
char *readdirectory(directory_type *dir) {}
void closedirectory(directory_type *dir) {}
