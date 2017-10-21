#define PROGRAM "tls"

/* These are to make syscall.o shut up. */
int dry_run = 0;
int read_only = 1;
int list_only = 0;
int preserve_perms = 0;


static void failed (char const *what,
		    char const *where)
{
	fprintf (stderr, PROGRAM ": %s %s: %s\n",
