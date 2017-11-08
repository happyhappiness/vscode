char *f_name(struct file_struct *f)
{
	static char names[5][MAXPATHLEN];
	static unsigned int n;

	n = (n + 1) % (sizeof names / sizeof names[0]);

	return f_name_to(f, names[n]);
}