static void list_file_entry(struct file_struct *f)
{
	char permbuf[PERMSTRING_SIZE];
	int64 len;
	int colwidth = human_readable ? 14 : 11;

	if (!F_IS_ACTIVE(f)) {
		/* this can happen if duplicate names were removed */
		return;
	}

	permstring(permbuf, f->mode);
	len = F_LENGTH(f);

	/* TODO: indicate '+' if the entry has an ACL. */

#ifdef SUPPORT_LINKS
	if (preserve_links && S_ISLNK(f->mode)) {
		rprintf(FINFO, "%s %*s %s %s -> %s\n",
			permbuf, colwidth, human_num(len),
			timestring(f->modtime), f_name(f, NULL),
			F_SYMLINK(f));
	} else
#endif
	if (missing_args == 2 && f->mode == 0) {
		rprintf(FINFO, "%-*s %s\n",
			colwidth + 31, "*missing",
			f_name(f, NULL));
	} else {
		rprintf(FINFO, "%s %*s %s %s\n",
			permbuf, colwidth, human_num(len),
			timestring(f->modtime), f_name(f, NULL));
	}
}