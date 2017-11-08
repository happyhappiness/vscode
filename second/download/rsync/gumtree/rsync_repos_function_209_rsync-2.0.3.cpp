char *f_name(struct file_struct *f)
{
	static char names[10][MAXPATHLEN];
	static int n;
	char *p = names[n];

	if (!f || !f->basename) return NULL;

	n = (n+1)%10;

	if (f->dirname) {
		sprintf(p, "%s/%s", f->dirname, f->basename);
	} else {
		strlcpy(p, f->basename, MAXPATHLEN-1);
	}

	return p;
}