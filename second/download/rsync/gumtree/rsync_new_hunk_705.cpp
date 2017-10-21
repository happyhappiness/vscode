static void finish_filelist_progress(const struct file_list *flist)
{
	if (do_progress) {
		/* This overwrites the progress line */
		rprintf(FINFO, "%d file%sto consider\n",
			flist->count, flist->count == 1 ? " " : "s ");
	} else
		rprintf(FINFO, "done\n");
}

void show_flist_stats(void)
{
	/* Nothing yet */
}


static void list_file_entry(struct file_struct *f)
{
	char perms[11];

	if (!f->basename)
		/* this can happen if duplicate names were removed */
		return;

	permstring(perms, f->mode);

#if SUPPORT_LINKS
	if (preserve_links && S_ISLNK(f->mode)) {
		rprintf(FINFO, "%s %11.0f %s %s -> %s\n",
			perms,
			(double) f->length, timestring(f->modtime),
			f_name(f), f->u.link);
	} else
#endif
		rprintf(FINFO, "%s %11.0f %s %s\n",
			perms,
			(double) f->length, timestring(f->modtime),
			f_name(f));
}


/**
 * Stat either a symlink or its referent, depending on the settings of
 * copy_links, copy_unsafe_links, etc.
