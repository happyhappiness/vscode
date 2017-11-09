char *f_name(const struct file_struct *f, char *fbuf)
{
	if (!f || !F_IS_ACTIVE(f))
		return NULL;

	if (!fbuf)
		fbuf = f_name_buf();

	if (f->dirname) {
		int len = strlen(f->dirname);
		memcpy(fbuf, f->dirname, len);
		fbuf[len] = '/';
		strlcpy(fbuf + len + 1, f->basename, MAXPATHLEN - (len + 1));
	} else
		strlcpy(fbuf, f->basename, MAXPATHLEN);

	return fbuf;
}