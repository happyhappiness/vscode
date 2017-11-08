static void list_file_entry(struct file_struct *f)
{
	char permbuf[PERMSTRING_SIZE];

	if (!f->basename) {
		/* this can happen if duplicate names were removed */
		return;
	}

	permstring(permbuf, f->mode);

#ifdef SUPPORT_LINKS
	if (preserve_links && S_ISLNK(f->mode)) {
		rprintf(FINFO, "%s %11.0f %s %s -> %s\n",
			permbuf,
			(double)f->length, timestring(f->modtime),
			f_name(f, NULL), f->u.link);
	} else
#endif
	{
		rprintf(FINFO, "%s %11.0f %s %s\n",
			permbuf,
			(double)f->length, timestring(f->modtime),
			f_name(f, NULL));
	}
}