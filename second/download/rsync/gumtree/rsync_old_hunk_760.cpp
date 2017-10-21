int dry_run = 0;
int read_only = 1;
int list_only = 0;
int preserve_perms = 0;


static void failed (char const *what,
		    char const *where)
{
	fprintf (stderr, PROGRAM ": %s %s: %s\n",
		 what, where, strerror (errno));
	exit (1);
}



static void list_file (const char *fname)
{
	STRUCT_STAT buf;
	char permbuf[PERMSTRING_SIZE];
	struct tm *mt;
	char datebuf[50];
	char linkbuf[4096];

	if (do_lstat(fname, &buf) == -1)
		failed ("stat", fname);

	/* The size of anything but a regular file is probably not
	 * worth thinking about. */
	if (!S_ISREG(buf.st_mode))
		buf.st_size = 0;

