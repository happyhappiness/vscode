struct file_list *send_file_list(int f, int argc, char *argv[])
{
	static const char *lastdir;
	static int lastdir_len = -1;
	int len, dirlen;
	STRUCT_STAT st;
	char *p, *dir;
	struct file_list *flist;
	struct timeval start_tv, end_tv;
	int64 start_write;
	int use_ff_fd = 0;
	int disable_buffering;
	int flags = recurse ? FLAG_CONTENT_DIR : 0;
	int reading_remotely = filesfrom_host != NULL;
	int rl_flags = (reading_remotely ? 0 : RL_DUMP_COMMENTS)
#ifdef ICONV_OPTION
		     | (filesfrom_convert ? RL_CONVERT : 0)
#endif
		     | (eol_nulls || reading_remotely ? RL_EOL_NULLS : 0);

	rprintf(FLOG, "building file list\n");
	if (show_filelist_p())
		start_filelist_progress("building file list");
	else if (inc_recurse && verbose && !am_server)
		rprintf(FCLIENT, "sending incremental file list\n");

	start_write = stats.total_written;
	gettimeofday(&start_tv, NULL);

	if (relative_paths && protocol_version >= 30)
		implied_dirs = 1; /* We send flagged implied dirs */

#ifdef SUPPORT_HARD_LINKS
	if (preserve_hard_links && protocol_version >= 30 && !cur_flist)
		init_hard_links();
#endif

	flist = cur_flist = flist_new(0, "send_file_list");
	if (inc_recurse) {
		dir_flist = flist_new(FLIST_TEMP, "send_file_list");
		flags |= FLAG_DIVERT_DIRS;
	} else
		dir_flist = cur_flist;

	disable_buffering = io_start_buffering_out(f);
	if (filesfrom_fd >= 0) {
		if (argv[0] && !push_dir(argv[0], 0)) {
			rsyserr(FERROR_XFER, errno, "push_dir %s failed in %s",
				full_fname(argv[0]), curr_dir);
			exit_cleanup(RERR_FILESELECT);
		}
		use_ff_fd = 1;
	}

	while (1) {
		char fbuf[MAXPATHLEN], *fn, name_type;

		if (use_ff_fd) {
			if (read_line(filesfrom_fd, fbuf, sizeof fbuf, rl_flags) == 0)
				break;
			sanitize_path(fbuf, fbuf, "", 0);
		} else {
			if (argc-- == 0)
				break;
			strlcpy(fbuf, *argv++, MAXPATHLEN);
			if (sanitize_paths)
				sanitize_path(fbuf, fbuf, "", 0);
		}

		len = strlen(fbuf);
		if (relative_paths) {
			/* We clean up fbuf below. */
			name_type = NORMAL_NAME;
		} else if (!len || fbuf[len - 1] == '/') {
			if (len == 2 && fbuf[0] == '.') {
				/* Turn "./" into just "." rather than "./." */
				fbuf[--len] = '\0';
			} else {
				if (len + 1 >= MAXPATHLEN)
					overflow_exit("send_file_list");
				fbuf[len++] = '.';
				fbuf[len] = '\0';
			}
			name_type = DOT_NAME;
		} else if (len > 1 && fbuf[len-1] == '.' && fbuf[len-2] == '.'
		    && (len == 2 || fbuf[len-3] == '/')) {
			if (len + 2 >= MAXPATHLEN)
				overflow_exit("send_file_list");
			fbuf[len++] = '/';
			fbuf[len++] = '.';
			fbuf[len] = '\0';
			name_type = DOT_NAME;
		} else if (fbuf[len-1] == '.' && (len == 1 || fbuf[len-2] == '/'))
			name_type = DOT_NAME;
		else
			name_type = NORMAL_NAME;

		dir = NULL;

		if (!relative_paths) {
			p = strrchr(fbuf, '/');
			if (p) {
				*p = '\0';
				if (p == fbuf)
					dir = "/";
				else
					dir = fbuf;
				len -= p - fbuf + 1;
				fn = p + 1;
			} else
				fn = fbuf;
		} else {
			if ((p = strstr(fbuf, "/./")) != NULL) {
				*p = '\0';
				if (p == fbuf)
					dir = "/";
				else
					dir = fbuf;
				fn = p + 3;
				while (*fn == '/')
					fn++;
				if (!*fn)
					*--fn = '\0'; /* ensure room for '.' */
			} else
				fn = fbuf;
			len = clean_fname(fn, CFN_KEEP_LEADING_DOT_DIR
					    | CFN_KEEP_TRAILING_SLASH
					    | CFN_DROP_TRAILING_DOT_DIR);
			if (len == 1) {
				if (fn[0] == '/') {
					fn = "/.";
					len = 2;
					name_type = DOT_NAME;
				} else if (fn[0] == '.')
					name_type = DOT_NAME;
			} else if (fn[len-1] == '/') {
				fn[--len] = '\0';
				if (len == 1 && *fn == '.')
					name_type = DOT_NAME;
				else
					name_type = SLASH_ENDING_NAME;
			}
			/* Reject a ".." dir in the active part of the path. */
			for (p = fn; (p = strstr(p, "..")) != NULL; p += 2) {
				if ((p[2] == '/' || p[2] == '\0')
				 && (p == fn || p[-1] == '/')) {
					rprintf(FERROR,
					    "found \"..\" dir in relative path: %s\n",
					    fn);
					exit_cleanup(RERR_SYNTAX);
				}
			}
		}

		if (!*fn) {
			len = 1;
			fn = ".";
			name_type = DOT_NAME;
		}

		dirlen = dir ? strlen(dir) : 0;
		if (dirlen != lastdir_len || memcmp(lastdir, dir, dirlen) != 0) {
			if (!push_pathname(dir ? strdup(dir) : NULL, dirlen))
				continue;
			lastdir = pathname;
			lastdir_len = pathname_len;
		} else if (!push_pathname(lastdir, lastdir_len))
			continue;

		if (fn != fbuf)
			memmove(fbuf, fn, len + 1);

		if (link_stat(fbuf, &st, copy_dirlinks || name_type != NORMAL_NAME) != 0) {
			io_error |= IOERR_GENERAL;
			rsyserr(FERROR_XFER, errno, "link_stat %s failed",
				full_fname(fbuf));
			continue;
		}

		if (S_ISDIR(st.st_mode) && !xfer_dirs) {
			rprintf(FINFO, "skipping directory %s\n", fbuf);
			continue;
		}

		if (inc_recurse && relative_paths && *fbuf) {
			if ((p = strchr(fbuf+1, '/')) != NULL) {
				if (p - fbuf == 1 && *fbuf == '.') {
					if ((fn = strchr(p+1, '/')) != NULL)
						p = fn;
				} else
					fn = p;
				send_implied_dirs(f, flist, fbuf, fbuf, p, flags, name_type);
				if (fn == p)
					continue;
			}
		} else if (implied_dirs && (p=strrchr(fbuf,'/')) && p != fbuf) {
			/* Send the implied directories at the start of the
			 * source spec, so we get their permissions right. */
			char *lp = lastpath, *slash = fbuf;
			*p = '\0';
			/* Skip any initial directories in our path that we
			 * have in common with lastpath. */
			for (fn = fbuf; *fn && *lp == *fn; lp++, fn++) {
				if (*fn == '/')
					slash = fn;
			}
			*p = '/';
			if (fn != p || (*lp && *lp != '/'))
				send_implied_dirs(f, flist, fbuf, slash, p, flags, 0);
		}

		if (one_file_system)
			filesystem_dev = st.st_dev;

		if (recurse || (xfer_dirs && name_type != NORMAL_NAME)) {
			struct file_struct *file;
			int top_flags = FLAG_TOP_DIR | FLAG_CONTENT_DIR | flags;
			file = send_file_name(f, flist, fbuf, &st,
					      top_flags, ALL_FILTERS);
			if (inc_recurse) {
				if (name_type == DOT_NAME && file) {
					if (send_dir_depth < 0) {
						send_dir_depth = 0;
						change_local_filter_dir(fbuf, len, send_dir_depth);
					}
					send_directory(f, flist, fbuf, len, flags);
				}
			} else if (file)
				send_if_directory(f, flist, file, fbuf, len, flags);
		} else
			send_file_name(f, flist, fbuf, &st, flags, ALL_FILTERS);
	}

	gettimeofday(&end_tv, NULL);
	stats.flist_buildtime = (int64)(end_tv.tv_sec - start_tv.tv_sec) * 1000
			      + (end_tv.tv_usec - start_tv.tv_usec) / 1000;
	if (stats.flist_buildtime == 0)
		stats.flist_buildtime = 1;
	start_tv = end_tv;

	write_byte(f, 0); /* Indicate end of file list */

#ifdef SUPPORT_HARD_LINKS
	if (preserve_hard_links && protocol_version >= 30 && !inc_recurse)
		idev_destroy();
#endif

	if (show_filelist_p())
		finish_filelist_progress(flist);

	gettimeofday(&end_tv, NULL);
	stats.flist_xfertime = (int64)(end_tv.tv_sec - start_tv.tv_sec) * 1000
			     + (end_tv.tv_usec - start_tv.tv_usec) / 1000;

	/* When converting names, both sides keep an unsorted file-list array
	 * because the names will differ on the sending and receiving sides
	 * (both sides will use the unsorted index number for each item). */

	/* Sort the list without removing any duplicates.  This allows the
	 * receiving side to ask for whatever name it kept.  For incremental
	 * recursion mode, the sender marks duplicate dirs so that it can
	 * send them together in a single file-list. */
	if (need_unsorted_flist) {
		if (!(flist->sorted = new_array(struct file_struct *, flist->used)))
			out_of_memory("send_file_list");
		memcpy(flist->sorted, flist->files,
		       flist->used * sizeof (struct file_struct*));
	} else
		flist->sorted = flist->files;
	flist_sort_and_clean(flist, 0);
	file_total += flist->used;

	if (numeric_ids <= 0 && !inc_recurse)
		send_id_list(f);

	/* send the io_error flag */
	if (protocol_version < 30)
		write_int(f, ignore_errors ? 0 : io_error);
	else if (io_error && !ignore_errors)
		send_msg_int(MSG_IO_ERROR, io_error);

	if (disable_buffering)
		io_end_buffering_out();

	stats.flist_size = stats.total_written - start_write;
	stats.num_files = flist->used;

	if (verbose > 3)
		output_flist(flist);

	if (verbose > 2)
		rprintf(FINFO, "send_file_list done\n");

	if (inc_recurse) {
		send_dir_depth = 1;
		add_dirs_to_tree(-1, flist, dir_count);
		if (!file_total || strcmp(flist->sorted[0]->basename, ".") != 0) 
			flist->parent_ndx = -1;
		flist_done_allocating(flist);
		if (send_dir_ndx < 0) {
			write_ndx(f, NDX_FLIST_EOF);
			flist_eof = 1;
		}
		else if (file_total == 1) {
			/* If we're creating incremental file-lists and there
			 * was just 1 item in the first file-list, send 1 more
			 * file-list to check if this is a 1-file xfer. */
			send_extra_file_list(f, 1);
		}
	}

	return flist;
}