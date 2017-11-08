static void list_file_entry(struct file_struct *f)
{
	char permbuf[PERMSTRING_SIZE];
	double len;

	if (!F_IS_ACTIVE(f)) {
		/* this can happen if duplicate names were removed */
		return;
	}

	permstring(permbuf, f->mode);
	len = F_LENGTH(f);

	/* TODO: indicate '+' if the entry has an ACL. */

#ifdef SUPPORT_LINKS
	if (preserve_links && S_ISLNK(f->mode)) {
		rprintf(FINFO, "%s %11.0f %s %s -> %s\n",
			permbuf, len, timestring(f->modtime),
			f_name(f, NULL), F_SYMLINK(f));
	} else
#endif
	{
		rprintf(FINFO, "%s %11.0f %s %s\n",
			permbuf, len, timestring(f->modtime),
			f_name(f, NULL));
	}
}