static void flist_sort_and_clean(struct file_list *flist, int strip_root)
{
	char fbuf[MAXPATHLEN];
	int i, prev_i;

	if (!flist)
		return;
	if (flist->used == 0) {
		flist->high = -1;
		flist->low = 0;
		return;
	}

	fsort(flist->sorted, flist->used);

	if (!am_sender || inc_recurse) {
		for (i = prev_i = 0; i < flist->used; i++) {
			if (F_IS_ACTIVE(flist->sorted[i])) {
				prev_i = i;
				break;
			}
		}
		flist->low = prev_i;
	} else {
		i = prev_i = flist->used - 1;
		flist->low = 0;
	}

	while (++i < flist->used) {
		int j;
		struct file_struct *file = flist->sorted[i];

		if (!F_IS_ACTIVE(file))
			continue;
		if (f_name_cmp(file, flist->sorted[prev_i]) == 0)
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
			int keep, drop;
			/* If one is a dir and the other is not, we want to
			 * keep the dir because it might have contents in the
			 * list.  Otherwise keep the first one. */
			if (S_ISDIR(file->mode)) {
				struct file_struct *fp = flist->sorted[j];
				if (!S_ISDIR(fp->mode))
					keep = i, drop = j;
				else {
					if (am_sender)
						file->flags |= FLAG_DUPLICATE;
					else { /* Make sure we merge our vital flags. */
						fp->flags |= file->flags & (FLAG_TOP_DIR|FLAG_CONTENT_DIR);
						fp->flags &= file->flags | ~FLAG_IMPLIED_DIR;
					}
					keep = j, drop = i;
				}
			} else
				keep = j, drop = i;

			if (!am_sender) {
				if (DEBUG_GTE(DUP, 1)) {
					rprintf(FINFO,
					    "removing duplicate name %s from file list (%d)\n",
					    f_name(file, fbuf), drop + flist->ndx_start);
				}
				clear_file(flist->sorted[drop]);
			}

			if (keep == i) {
				if (flist->low == drop) {
					for (j = drop + 1;
					     j < i && !F_IS_ACTIVE(flist->sorted[j]);
					     j++) {}
					flist->low = j;
				}
				prev_i = i;
			}
		} else
			prev_i = i;
	}
	flist->high = prev_i;

	if (strip_root) {
		/* We need to strip off the leading slashes for relative
		 * paths, but this must be done _after_ the sorting phase. */
		for (i = flist->low; i <= flist->high; i++) {
			struct file_struct *file = flist->sorted[i];

			if (!file->dirname)
				continue;
			while (*file->dirname == '/')
				file->dirname++;
			if (!*file->dirname)
				file->dirname = NULL;
		}
	}

	if (prune_empty_dirs && !am_sender) {
		int j, prev_depth = 0;

		prev_i = 0; /* It's OK that this isn't really true. */

		for (i = flist->low; i <= flist->high; i++) {
			struct file_struct *fp, *file = flist->sorted[i];

			/* This temporarily abuses the F_DEPTH() value for a
			 * directory that is in a chain that might get pruned.
			 * We restore the old value if it gets a reprieve. */
			if (S_ISDIR(file->mode) && F_DEPTH(file)) {
				/* Dump empty dirs when coming back down. */
				for (j = prev_depth; j >= F_DEPTH(file); j--) {
					fp = flist->sorted[prev_i];
					if (F_DEPTH(fp) >= 0)
						break;
					prev_i = -F_DEPTH(fp)-1;
					clear_file(fp);
				}
				prev_depth = F_DEPTH(file);
				if (is_excluded(f_name(file, fbuf), 1,
						       ALL_FILTERS)) {
					/* Keep dirs through this dir. */
					for (j = prev_depth-1; ; j--) {
						fp = flist->sorted[prev_i];
						if (F_DEPTH(fp) >= 0)
							break;
						prev_i = -F_DEPTH(fp)-1;
						F_DEPTH(fp) = j;
					}
				} else
					F_DEPTH(file) = -prev_i-1;
				prev_i = i;
			} else {
				/* Keep dirs through this non-dir. */
				for (j = prev_depth; ; j--) {
					fp = flist->sorted[prev_i];
					if (F_DEPTH(fp) >= 0)
						break;
					prev_i = -F_DEPTH(fp)-1;
					F_DEPTH(fp) = j;
				}
			}
		}
		/* Dump all remaining empty dirs. */
		while (1) {
			struct file_struct *fp = flist->sorted[prev_i];
			if (F_DEPTH(fp) >= 0)
				break;
			prev_i = -F_DEPTH(fp)-1;
			clear_file(fp);
		}

		for (i = flist->low; i <= flist->high; i++) {
			if (F_IS_ACTIVE(flist->sorted[i]))
				break;
		}
		flist->low = i;
		for (i = flist->high; i >= flist->low; i--) {
			if (F_IS_ACTIVE(flist->sorted[i]))
				break;
		}
		flist->high = i;
	}
}