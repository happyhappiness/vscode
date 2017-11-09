static void send1extra(int f, struct file_struct *file, struct file_list *flist)
{
	char fbuf[MAXPATHLEN];
	item_list *relname_list;
	int len, dlen, flags = FLAG_DIVERT_DIRS | FLAG_CONTENT_DIR;
	size_t j;

	f_name(file, fbuf);
	dlen = strlen(fbuf);

	if (!change_pathname(file, NULL, 0))
		exit_cleanup(RERR_FILESELECT);

	change_local_filter_dir(fbuf, dlen, send_dir_depth);

	if (file->flags & FLAG_CONTENT_DIR) {
		if (one_file_system) {
			STRUCT_STAT st;
			if (link_stat(fbuf, &st, copy_dirlinks) != 0) {
				interpret_stat_error(fbuf, True);
				return;
			}
			filesystem_dev = st.st_dev;
		}
		send_directory(f, flist, fbuf, dlen, flags);
	}

	if (!relative_paths)
		return;

	memcpy(&relname_list, F_DIR_RELNAMES_P(file), sizeof relname_list);
	if (!relname_list)
		return;

	for (j = 0; j < relname_list->count; j++) {
		char *slash;
		relnamecache *rnp = ((relnamecache**)relname_list->items)[j];
		char name_type = rnp->name_type;

		fbuf[dlen] = '/';
		len = strlcpy(fbuf + dlen + 1, rnp->fname, sizeof fbuf - dlen - 1);
		free(rnp);
		if (len >= (int)sizeof fbuf)
			continue; /* Impossible... */

		slash = strchr(fbuf+dlen+1, '/');
		if (slash) {
			send_implied_dirs(f, flist, fbuf, fbuf+dlen+1, slash, flags, name_type);
			continue;
		}

		if (name_type != NORMAL_NAME) {
			STRUCT_STAT st;
			if (name_type == MISSING_NAME)
				memset(&st, 0, sizeof st);
			else if (link_stat(fbuf, &st, 1) != 0) {
				interpret_stat_error(fbuf, True);
				continue;
			}
			send_file_name(f, flist, fbuf, &st, FLAG_TOP_DIR | flags, ALL_FILTERS);
		} else
			send_file_name(f, flist, fbuf, NULL, FLAG_TOP_DIR | flags, ALL_FILTERS);
	}

	free(relname_list);
}