static void output_flist(struct file_list *flist)
{
	char uidbuf[16], gidbuf[16], depthbuf[16];
	struct file_struct *file;
	const char *who = who_am_i();
	int i;

	for (i = 0; i < flist->count; i++) {
		file = flist->files[i];
		if ((am_root || am_sender) && preserve_uid)
			sprintf(uidbuf, " uid=%ld", (long)file->uid);
		else
			*uidbuf = '\0';
		if (preserve_gid && file->gid != GID_NONE)
			sprintf(gidbuf, " gid=%ld", (long)file->gid);
		else
			*gidbuf = '\0';
		if (!am_sender)
			sprintf(depthbuf, "%d", file->dir.depth);
		rprintf(FINFO, "[%s] i=%d %s %s%s%s%s mode=0%o len=%.0f%s%s flags=%x\n",
			who, i, am_sender ? NS(file->dir.root) : depthbuf,
			file->dirname ? file->dirname : "",
			file->dirname ? "/" : "", NS(file->basename),
			S_ISDIR(file->mode) ? "/" : "", (int)file->mode,
			(double)file->length, uidbuf, gidbuf, file->flags);
	}
}