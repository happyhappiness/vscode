char *f_name(struct file_struct *f)
{
	static char names[10][MAXPATHLEN];
	static int n;
	char *p = names[n];

	if (!f || !f->basename)
		return NULL;

	n = (n + 1) % 10;

	if (f->dirname) {
		int off;

		off = strlcpy(p, f->dirname, MAXPATHLEN);
		off += strlcpy(p + off, "/", MAXPATHLEN - off);
		off += strlcpy(p + off, f->basename, MAXPATHLEN - off);
	} else {
		strlcpy(p, f->basename, MAXPATHLEN);
	}

	return p;
}