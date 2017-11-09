static void output_flist(struct file_list *flist)
{
	char uidbuf[16], gidbuf[16], depthbuf[16];
	struct file_struct *file;
	const char *root, *dir, *slash, *name, *trail;
	const char *who = who_am_i();
	int i;

	rprintf(FINFO, "[%s] flist start=%d, used=%d, low=%d, high=%d\n",
		who, flist->ndx_start, flist->used, flist->low, flist->high);
	for (i = 0; i < flist->used; i++) {
		file = flist->files[i];
		if ((am_root || am_sender) && uid_ndx) {
			snprintf(uidbuf, sizeof uidbuf, " uid=%u",
				 F_OWNER(file));
		} else
			*uidbuf = '\0';
		if (gid_ndx) {
			static char parens[] = "(\0)\0\0\0";
			char *pp = parens + (file->flags & FLAG_SKIP_GROUP ? 0 : 3);
			snprintf(gidbuf, sizeof gidbuf, " gid=%s%u%s",
				 pp, F_GROUP(file), pp + 2);
		} else
			*gidbuf = '\0';
		if (!am_sender)
			snprintf(depthbuf, sizeof depthbuf, "%d", F_DEPTH(file));
		if (F_IS_ACTIVE(file)) {
			root = am_sender ? NS(F_PATHNAME(file)) : depthbuf;
			if ((dir = file->dirname) == NULL)
				dir = slash = "";
			else
				slash = "/";
			name = file->basename;
			trail = S_ISDIR(file->mode) ? "/" : "";
		} else
			root = dir = slash = name = trail = "";
		rprintf(FINFO,
			"[%s] i=%d %s %s%s%s%s mode=0%o len=%s%s%s flags=%x\n",
			who, i + flist->ndx_start,
			root, dir, slash, name, trail,
			(int)file->mode, comma_num(F_LENGTH(file)),
			uidbuf, gidbuf, file->flags);
	}
}