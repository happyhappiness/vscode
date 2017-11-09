static void send_implied_dirs(int f, struct file_list *flist, char *fname,
			      char *start, char *limit, int flags, char name_type)
{
	static char lastpath[MAXPATHLEN] = "";
	static int lastpath_len = 0;
	static struct file_struct *lastpath_struct = NULL;
	struct file_struct *file;
	item_list *relname_list;
	relnamecache **rnpp;
	int len, need_new_dir, depth = 0;
	filter_rule_list save_filter_list = filter_list;

	flags = (flags | FLAG_IMPLIED_DIR) & ~(FLAG_TOP_DIR | FLAG_CONTENT_DIR);
	filter_list.head = filter_list.tail = NULL; /* Don't filter implied dirs. */

	if (inc_recurse) {
		if (lastpath_struct && F_PATHNAME(lastpath_struct) == pathname
		 && lastpath_len == limit - fname
		 && strncmp(lastpath, fname, lastpath_len) == 0)
			need_new_dir = 0;
		else
			need_new_dir = 1;
	} else {
		char *tp = fname, *lp = lastpath;
		/* Skip any initial directories in our path that we
		 * have in common with lastpath. */
		assert(start == fname);
		for ( ; ; tp++, lp++) {
			if (tp == limit) {
				if (*lp == '/' || *lp == '\0')
					goto done;
				break;
			}
			if (*lp != *tp)
				break;
			if (*tp == '/') {
				start = tp;
				depth++;
			}
		}
		need_new_dir = 1;
	}

	if (need_new_dir) {
		int save_copy_links = copy_links;
		int save_xfer_dirs = xfer_dirs;
		char *slash;

		copy_links = xfer_dirs = 1;

		*limit = '\0';

		for (slash = start; (slash = strchr(slash+1, '/')) != NULL; ) {
			*slash = '\0';
			file = send_file_name(f, flist, fname, NULL, flags, ALL_FILTERS);
			depth++;
			if (!inc_recurse && file && S_ISDIR(file->mode))
				change_local_filter_dir(fname, strlen(fname), depth);
			*slash = '/';
		}

		file = send_file_name(f, flist, fname, NULL, flags, ALL_FILTERS);
		if (inc_recurse) {
			if (file && !S_ISDIR(file->mode))
				file = NULL;
			lastpath_struct = file;
		} else if (file && S_ISDIR(file->mode))
			change_local_filter_dir(fname, strlen(fname), ++depth);

		strlcpy(lastpath, fname, sizeof lastpath);
		lastpath_len = limit - fname;

		*limit = '/';

		copy_links = save_copy_links;
		xfer_dirs = save_xfer_dirs;

		if (!inc_recurse)
			goto done;
	}

	if (!lastpath_struct)
		goto done; /* dir must have vanished */

	len = strlen(limit+1);
	memcpy(&relname_list, F_DIR_RELNAMES_P(lastpath_struct), sizeof relname_list);
	if (!relname_list) {
		if (!(relname_list = new0(item_list)))
			out_of_memory("send_implied_dirs");
		memcpy(F_DIR_RELNAMES_P(lastpath_struct), &relname_list, sizeof relname_list);
	}
	rnpp = EXPAND_ITEM_LIST(relname_list, relnamecache *, 32);
	if (!(*rnpp = (relnamecache*)new_array(char, sizeof (relnamecache) + len)))
		out_of_memory("send_implied_dirs");
	(*rnpp)->name_type = name_type;
	strlcpy((*rnpp)->fname, limit+1, len + 1);

done:
	filter_list = save_filter_list;
}