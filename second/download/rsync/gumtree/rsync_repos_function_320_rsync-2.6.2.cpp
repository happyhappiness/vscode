static void output_flist(struct file_list *flist)
{
	char uidbuf[16], gidbuf[16];
	struct file_struct *file;
	int i;

	for (i = 0; i < flist->count; i++) {
		file = flist->files[i];
		if (am_root && preserve_uid)
			sprintf(uidbuf, " uid=%ld", (long)file->uid);
		else
			*uidbuf = '\0';
		if (preserve_gid && file->gid != GID_NONE)
			sprintf(gidbuf, " gid=%ld", (long)file->gid);
		else
			*gidbuf = '\0';
		rprintf(FINFO, "[%s] i=%d %s %s %s mode=0%o len=%.0f%s%s\n",
			who_am_i(), i, NS(file->basedir), NS(file->dirname),
			NS(file->basename), (int) file->mode,
			(double) file->length, uidbuf, gidbuf);
	}
}