static void clean_flist(struct file_list *flist, int strip_root, int no_dups)
{
	int i, prev_i = 0;
	char *name, *prev_name = NULL;

	if (!flist || flist->count == 0)
		return;

	qsort(flist->files, flist->count,
	      sizeof(flist->files[0]), (int (*)()) file_compare);

	for (i = no_dups? 0 : flist->count; i < flist->count; i++) {
		if (flist->files[i]->basename) {
			prev_i = i;
			prev_name = f_name(flist->files[i]);
			break;
		}
	}
	while (++i < flist->count) {
		if (!flist->files[i]->basename)
			continue;
		name = f_name(flist->files[i]);
		if (strcmp(name, prev_name) == 0) {
			if (verbose > 1 && !am_server) {
				rprintf(FINFO,
					"removing duplicate name %s from file list %d\n",
					name, i);
			}
			/* Make sure that if we unduplicate '.', that we don't
			 * lose track of a user-specified starting point (or
			 * else deletions will mysteriously fail with -R). */
			if (flist->files[i]->flags & FLAG_DELETE)
				flist->files[prev_i]->flags |= FLAG_DELETE;
			/* it's not great that the flist knows the semantics of
			 * the file memory usage, but i'd rather not add a flag
			 * byte to that struct.
			 * XXX can i use a bit in the flags field? */
			if (flist->string_area)
				flist->files[i][0] = null_file;
			else
				free_file(flist->files[i]);
		}
		else
			prev_i = i;
		/* We set prev_name every iteration to avoid it becoming
		 * invalid when names[][] in f_name() wraps around. */
		prev_name = name;
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