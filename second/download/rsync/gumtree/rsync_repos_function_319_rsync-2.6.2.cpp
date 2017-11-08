static void clean_flist(struct file_list *flist, int strip_root, int no_dups)
{
	int i, prev_i = 0;

	if (!flist || flist->count == 0)
		return;

	qsort(flist->files, flist->count,
	    sizeof flist->files[0], (int (*)()) file_compare);

	for (i = no_dups? 0 : flist->count; i < flist->count; i++) {
		if (flist->files[i]->basename) {
			prev_i = i;
			break;
		}
	}
	while (++i < flist->count) {
		if (!flist->files[i]->basename)
			continue;
		if (f_name_cmp(flist->files[i], flist->files[prev_i]) == 0) {
			if (verbose > 1 && !am_server) {
				rprintf(FINFO,
					"removing duplicate name %s from file list %d\n",
					f_name(flist->files[i]), i);
			}
			/* Make sure that if we unduplicate '.', that we don't
			 * lose track of a user-specified starting point (or
			 * else deletions will mysteriously fail with -R). */
			if (flist->files[i]->flags & FLAG_TOP_DIR)
				flist->files[prev_i]->flags |= FLAG_TOP_DIR;

			clear_file(i, flist);
		} else
			prev_i = i;
	}

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
}