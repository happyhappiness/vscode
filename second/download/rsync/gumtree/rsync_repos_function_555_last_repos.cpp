char *f_name_buf(void)
{
	static char names[5][MAXPATHLEN];
	static unsigned int n;

	n = (n + 1) % (sizeof names / sizeof names[0]);

	return names[n];
}