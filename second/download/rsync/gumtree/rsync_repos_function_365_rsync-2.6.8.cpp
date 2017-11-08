static void clean_flist(struct file_list *flist, int strip_root, int no_dups)
{
	char fbuf[MAXPATHLEN];
	int i, prev_i = 0;

	if (!flist)
		return;
	if (flist->count == 0) {
		flist->high = -1;
		return;
	}

	qsort(flist->files, flist->count,
	    sizeof flist->files[0], (int (*)())file_compare);

	for (i = no_dups? 0 : flist->count; i < flist->count; i++) {
		if (flist->files[i]->basename) {
			prev_i = i;
			break;
		}
	}
	flist->low = prev_i;
	while (++i < flist->count) {
		int j;
		struct file_struct *file = flist->files[i];

		if (!file->basename)
			continue;
		if (f_name_cmp(file, flist->files[prev_i]) == 0)
			j = prev_i;
		else if (protocol_version >= 29 && S_ISDIR(file->mode)) {
			int save_mode = file->mode;
			/* Make sure that this directory doesn't duplicate a
			 * non-directory earlier in the list. */
			flist->high = prev_i;
			file->mode = S_IFREG;
			j = flist_find(flist, file);
			file->mode = save_mode;
		} else
			j = -1;
		if (j >= 0) {
			struct file_struct *fp = flist->files[j];
			int keep, drop;
			/* If one is a dir and the other is not, we want to
			 * keep the dir because it might have contents in the
			 * list. */
			if (S_ISDIR(file->mode) != S_ISDIR(fp->mode)) {
				if (S_ISDIR(file->mode))
					keep = i, drop = j;
				else
					keep = j, drop = i;
			} else
				keep = j, drop = i;
			if (verbose > 1 && !am_server) {
				rprintf(FINFO,
					"removing duplicate name %s from file list (%d)\n",
					f_name(file, fbuf), drop);
			}
			/* Make sure we don't lose track of a user-specified
			 * top directory. */
			flist->files[keep]->flags |= flist->files[drop]->flags
						   & (FLAG_TOP_DIR|FLAG_DEL_HERE);

			clear_file(flist->files[drop], flist);

			if (keep == i) {
				if (flist->low == drop) {
					for (j = drop + 1;
					     j < i && !flist->files[j]->basename;
					     j++) {}
					flist->low = j;
				}
				prev_i = i;
			}
		} else
			prev_i = i;
	}
	flist->high = no_dups ? prev_i : flist->count - 1;

	if (strip_root) {
		/* We need to strip off the leading slashes for relative
		 * paths, but this must be done _after_ the sorting phase. */
		for (i = flist->low; i <= flist->high; i++) {
			struct file_struct *file = flist->files[i];

			if (!file->dirname)
				continue;
			while (*file->dirname == '/')
				file->dirname++;
			if (!*file->dirname)
				file->dirname = NULL;
		}
	}

	if (prune_empty_dirs && no_dups) {
		int j, prev_depth = 0;

		prev_i = 0; /* It's OK that this isn't really true. */

		for (i = flist->low; i <= flist->high; i++) {
			struct file_struct *fp, *file = flist->files[i];

			/* This temporarily abuses the dir.depth value for a
			 * directory that is in a chain that might get pruned.
			 * We restore the old value if it gets a reprieve. */
			if (S_ISDIR(file->mode) && file->dir.depth) {
				/* Dump empty dirs when coming back down. */
				for (j = prev_depth; j >= file->dir.depth; j--) {
					fp = flist->files[prev_i];
					if (fp->dir.depth >= 0)
						break;
					prev_i = -fp->dir.depth-1;
					clear_file(fp, flist);
				}
				prev_depth = file->dir.depth;
				if (is_excluded(f_name(file, fbuf), 1,
						       ALL_FILTERS)) {
					/* Keep dirs through this dir. */
					for (j = prev_depth-1; ; j--) {
						fp = flist->files[prev_i];
						if (fp->dir.depth >= 0)
							break;
						prev_i = -fp->dir.depth-1;
						fp->dir.depth = j;
					}
				} else
					file->dir.depth = -prev_i-1;
				prev_i = i;
			} else {
				/* Keep dirs through this non-dir. */
				for (j = prev_depth; ; j--) {
					fp = flist->files[prev_i];
					if (fp->dir.depth >= 0)
						break;
					prev_i = -fp->dir.depth-1;
					fp->dir.depth = j;
				}
			}
		}
		/* Dump empty all remaining empty dirs. */
		while (1) {
			struct file_struct *fp = flist->files[prev_i];
			if (fp->dir.depth >= 0)
				break;
			prev_i = -fp->dir.depth-1;
			clear_file(fp, flist);
		}

		for (i = flist->low; i <= flist->high; i++) {
			if (flist->files[i]->basename)
				break;
		}
		flist->low = i;
		for (i = flist->high; i >= flist->low; i--) {
			if (flist->files[i]->basename)
				break;
		}
		flist->high = i;
	}
}