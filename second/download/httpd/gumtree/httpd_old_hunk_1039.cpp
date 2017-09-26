#include <stdio.h>
#include <string.h>
#include <pcre.h>

/* Compile thuswise:
  gcc -Wall pcredemo.c -I/opt/local/include -L/opt/local/lib \
    -R/opt/local/lib -lpcre
*/

#define OVECCOUNT 30    /* should be a multiple of 3 */

int main(int argc, char **argv)
{
pcre *re;
const char *error;
int erroffset;
int ovector[OVECCOUNT];
int rc, i;

if (argc != 3)
  {
  printf("Two arguments required: a regex and a subject string\n");
  return 1;
  }

/* Compile the regular expression in the first argument */

re = pcre_compile(
  argv[1],              /* the pattern */
  0,                    /* default options */
  &error,               /* for error message */
  &erroffset,           /* for error offset */
  NULL);                /* use default character tables */

/* Compilation failed: print the error message and exit */
