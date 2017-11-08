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
		strlcpy(fbuf + len + 1, f->basename, MAXPATHLEN - (len + 1));
	} else
		strlcpy(fbuf, f->basename, MAXPATHLEN);

	return fbuf;
}