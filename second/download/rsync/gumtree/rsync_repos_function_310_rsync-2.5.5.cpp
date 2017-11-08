static void clean_flist(struct file_list *flist, int strip_root)
{
	int i;

	if (!flist || flist->count == 0)
		return;

	qsort(flist->files, flist->count,
	      sizeof(flist->files[0]), (int (*)()) file_compare);

	for (i = 1; i < flist->count; i++) {
		if (flist->files[i]->basename &&
		    flist->files[i - 1]->basename &&
		    strcmp(f_name(flist->files[i]),
			   f_name(flist->files[i - 1])) == 0) {
			if (verbose > 1 && !am_server)
				rprintf(FINFO,
					"removing duplicate name %s from file list %d\n",
					f_name(flist->files[i - 1]),
					i - 1);
			/* it's not great that the flist knows the semantics of the
			 * file memory usage, but i'd rather not add a flag byte
			 * to that struct. XXX can i use a bit in the flags field? */
			if (flist->string_area)
				flist->files[i][0] = null_file;
			else
				free_file(flist->files[i]);
		}
	}

	/* FIXME: There is a bug here when filenames are repeated more
	 * than once, because we don't handle freed files when doing
	 * the comparison. */

	if (strip_root) {
		/* we need to strip off the root directory in the case
		   of relative paths, but this must be done _after_
		   the sorting phase */
		for (i = 0; i < flist->count; i++) {
			if (flist->files[i]->dirname &&
			    flist->files[i]->dirname[0] == '/') {
				memmove(&flist->files[i]->dirname[0],
					&flist->files[i]->dirname[1],
					strlen(flist->files[i]->dirname));
			}

			if (flist->files[i]->dirname &&
			    !flist->files[i]->dirname[0]) {
				flist->files[i]->dirname = NULL;
			}
		}
	}


	if (verbose <= 3)
		return;

	for (i = 0; i < flist->count; i++) {
		rprintf(FINFO, "[%d] i=%d %s %s mode=0%o len=%.0f\n",
			(int) getpid(), i,
			NS(flist->files[i]->dirname),
			NS(flist->files[i]->basename),
			(int) flist->files[i]->mode,
			(double) flist->files[i]->length);
	}
}