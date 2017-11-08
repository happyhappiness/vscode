char *f_name(struct file_struct *f, char *fbuf)
{
	if (!f || !f->basename)
		return NULL;

	if (!fbuf) {
		static char names[5][MAXPATHLEN];
		static unsigned int n;

		n = (n + 1) % (sizeof names / sizeof names[0]);

		fbuf = names[n];
	}

	if (f->dirname) {
		int len = strlen(f->dirname);
		memcpy(fbuf, f->dirname, len);
		fbuf[len] = '/';
		strcpy(fbuf + len + 1, f->basename);
	} else
		strcpy(fbuf, f->basename);

	return fbuf;
}