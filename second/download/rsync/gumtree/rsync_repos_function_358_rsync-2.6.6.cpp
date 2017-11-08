char *f_name_to(struct file_struct *f, char *fbuf)
{
	if (!f || !f->basename)
		return NULL;

	if (f->dirname) {
		int len = strlen(f->dirname);
		memcpy(fbuf, f->dirname, len);
		fbuf[len] = '/';
		strcpy(fbuf + len + 1, f->basename);
	} else
		strcpy(fbuf, f->basename);
	return fbuf;
}