}

/*
 * Free up any resources a file_struct has allocated
 * and clear the file.
 */
void clear_file(struct file_struct *file, struct file_list *flist)
{
	if (flist->hlink_pool && file->link_u.idev)
		pool_free(flist->hlink_pool, 0, file->link_u.idev);
	memset(file, 0, file_struct_len);
	/* In an empty entry, dir.depth is an offset to the next non-empty
	 * entry.  Likewise for length in the opposite direction.  We assume
	 * that we're alone for now since flist_find() will adjust the counts
	 * it runs into that aren't up-to-date. */
	file->length = file->dir.depth = 1;
}

/*
 * allocate a new file list
 */
struct file_list *flist_new(int with_hlink, char *msg)
{
	struct file_list *flist;

	flist = new(struct file_list);
	if (!flist)
		out_of_memory(msg);

	memset(flist, 0, sizeof (struct file_list));

	if (!(flist->file_pool = pool_create(FILE_EXTENT, 0,
	    out_of_memory, POOL_INTERN)))
		out_of_memory(msg);

#ifdef SUPPORT_HARD_LINKS
	if (with_hlink && preserve_hard_links) {
		if (!(flist->hlink_pool = pool_create(HLINK_EXTENT,
		    sizeof (struct idev), out_of_memory, POOL_INTERN)))
			out_of_memory(msg);
	}
#endif

	return flist;
}

/*
 * free up all elements in a flist
 */
void flist_free(struct file_list *flist)
{
	pool_destroy(flist->file_pool);
	pool_destroy(flist->hlink_pool);
	free(flist->files);
	free(flist);
}

/*
 * This routine ensures we don't have any duplicate names in our file list.
 * duplicate names can cause corruption because of the pipelining
 */
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

static void output_flist(struct file_list *flist)
{
	char uidbuf[16], gidbuf[16], depthbuf[16];
	struct file_struct *file;
	const char *who = who_am_i();
	int i;

	for (i = 0; i < flist->count; i++) {
		file = flist->files[i];
		if ((am_root || am_sender) && preserve_uid)
			snprintf(uidbuf, sizeof uidbuf, " uid=%ld", (long)file->uid);
		else
			*uidbuf = '\0';
		if (preserve_gid && file->gid != GID_NONE)
			snprintf(gidbuf, sizeof gidbuf, " gid=%ld", (long)file->gid);
		else
			*gidbuf = '\0';
		if (!am_sender)
			snprintf(depthbuf, sizeof depthbuf, "%d", file->dir.depth);
		rprintf(FINFO, "[%s] i=%d %s %s%s%s%s mode=0%o len=%.0f%s%s flags=%x\n",
			who, i, am_sender ? NS(file->dir.root) : depthbuf,
			file->dirname ? file->dirname : "",
			file->dirname ? "/" : "", NS(file->basename),
			S_ISDIR(file->mode) ? "/" : "", (int)file->mode,
			(double)file->length, uidbuf, gidbuf, file->flags);
	}
}

enum fnc_state { s_DIR, s_SLASH, s_BASE, s_TRAILING };
enum fnc_type { t_PATH, t_ITEM };

/* Compare the names of two file_struct entities, similar to how strcmp()
 * would do if it were operating on the joined strings.
 *
 * Some differences beginning with protocol_version 29: (1) directory names
 * are compared with an assumed trailing slash so that they compare in a
 * way that would cause them to sort immediately prior to any content they
