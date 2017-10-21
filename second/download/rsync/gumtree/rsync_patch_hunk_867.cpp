 			io_error |= IOERR_GENERAL;
 			rprintf(FINFO,
 				"cannot send long-named file %s\n",
 				full_fname(fbuf));
 			continue;
 		}
+		if (dname[0] == '\0') {
+			io_error |= IOERR_GENERAL;
+			rprintf(FINFO,
+				"cannot send file with empty name in %s\n",
+				full_fname(fbuf));
+			continue;
+		}
 
-		send_file_name(f, flist, fbuf, NULL, 0);
+		send_file_name(f, flist, fbuf, NULL, flags, filter_level);
 	}
 
 	fbuf[len] = '\0';
 
 	if (errno) {
 		io_error |= IOERR_GENERAL;
-		rsyserr(FERROR, errno, "readdir(%s)", full_fname(fbuf));
+		rsyserr(FERROR_XFER, errno, "readdir(%s)", full_fname(fbuf));
 	}
 
 	closedir(d);
 
-	if (recurse) {
-		int i, end = flist->count - 1;
+	if (f >= 0 && recurse && !divert_dirs) {
+		int i, end = flist->used - 1;
+		/* send_if_directory() bumps flist->used, so use "end". */
 		for (i = start; i <= end; i++)
-			send_if_directory(f, flist, flist->files[i], fbuf, len);
+			send_if_directory(f, flist, flist->files[i], fbuf, len, flags);
+	}
+}
+
+static char lastpath[MAXPATHLEN] = "";
+static int lastpath_len = 0;
+static struct file_struct *lastpath_struct;
+
+static void send_implied_dirs(int f, struct file_list *flist, char *fname,
+			      char *start, char *limit, int flags, char name_type)
+{
+	struct file_struct *file;
+	item_list *relname_list;
+	relnamecache **rnpp;
+	char *slash;
+	int len, need_new_dir;
+	struct filter_list_struct save_filter_list = filter_list;
+
+	flags = (flags | FLAG_IMPLIED_DIR) & ~(FLAG_TOP_DIR | FLAG_CONTENT_DIR);
+	filter_list.head = filter_list.tail = NULL; /* Don't filter implied dirs. */
+
+	if (inc_recurse) {
+		if (lastpath_struct && F_PATHNAME(lastpath_struct) == pathname
+		 && lastpath_len == limit - fname
+		 && strncmp(lastpath, fname, lastpath_len) == 0)
+			need_new_dir = 0;
+		else
+			need_new_dir = 1;
+	} else
+		need_new_dir = 1;
+
+	if (need_new_dir) {
+		int save_copy_links = copy_links;
+		int save_xfer_dirs = xfer_dirs;
+
+		copy_links = xfer_dirs = 1;
+
+		*limit = '\0';
+
+		for (slash = start; (slash = strchr(slash+1, '/')) != NULL; ) {
+			*slash = '\0';
+			send_file_name(f, flist, fname, NULL, flags, ALL_FILTERS);
+			*slash = '/';
+		}
+
+		file = send_file_name(f, flist, fname, NULL, flags, ALL_FILTERS);
+		if (inc_recurse) {
+			if (file && !S_ISDIR(file->mode))
+				file = NULL;
+			lastpath_struct = file;
+		}
+
+		strlcpy(lastpath, fname, sizeof lastpath);
+		lastpath_len = limit - fname;
+
+		*limit = '/';
+
+		copy_links = save_copy_links;
+		xfer_dirs = save_xfer_dirs;
+
+		if (!inc_recurse)
+			goto done;
+	}
+
+	if (!lastpath_struct)
+		goto done; /* dir must have vanished */
+
+	len = strlen(limit+1);
+	memcpy(&relname_list, F_DIR_RELNAMES_P(lastpath_struct), sizeof relname_list);
+	if (!relname_list) {
+		if (!(relname_list = new0(item_list)))
+			out_of_memory("send_implied_dirs");
+		memcpy(F_DIR_RELNAMES_P(lastpath_struct), &relname_list, sizeof relname_list);
+	}
+	rnpp = EXPAND_ITEM_LIST(relname_list, relnamecache *, 32);
+	if (!(*rnpp = (relnamecache*)new_array(char, sizeof (relnamecache) + len)))
+		out_of_memory("send_implied_dirs");
+	(*rnpp)->name_type = name_type;
+	strlcpy((*rnpp)->fname, limit+1, len + 1);
+
+done:
+	filter_list = save_filter_list;
+}
+
+static void send1extra(int f, struct file_struct *file, struct file_list *flist)
+{
+	char fbuf[MAXPATHLEN];
+	item_list *relname_list;
+	int len, dlen, flags = FLAG_DIVERT_DIRS | FLAG_CONTENT_DIR;
+	size_t j;
+
+	f_name(file, fbuf);
+	dlen = strlen(fbuf);
+
+	if (F_PATHNAME(file) != pathname) {
+		if (!push_pathname(F_PATHNAME(file), -1))
+			exit_cleanup(RERR_FILESELECT);
+	}
+
+	change_local_filter_dir(fbuf, dlen, send_dir_depth);
+
+	if (file->flags & FLAG_CONTENT_DIR) {
+		if (one_file_system) {
+			STRUCT_STAT st;
+			if (link_stat(fbuf, &st, copy_dirlinks) != 0) {
+				io_error |= IOERR_GENERAL;
+				rsyserr(FERROR_XFER, errno, "link_stat %s failed",
+					full_fname(fbuf));
+				return;
+			}
+			filesystem_dev = st.st_dev;
+		}
+		send_directory(f, flist, fbuf, dlen, flags);
+	}
+
+	if (!relative_paths)
+		return;
+
+	memcpy(&relname_list, F_DIR_RELNAMES_P(file), sizeof relname_list);
+	if (!relname_list)
+		return;
+
+	for (j = 0; j < relname_list->count; j++) {
+		char *slash;
+		relnamecache *rnp = ((relnamecache**)relname_list->items)[j];
+		char name_type = rnp->name_type;
+
+		fbuf[dlen] = '/';
+		len = strlcpy(fbuf + dlen + 1, rnp->fname, sizeof fbuf - dlen - 1);
+		free(rnp);
+		if (len >= (int)sizeof fbuf)
+			continue; /* Impossible... */
+
+		slash = strchr(fbuf+dlen+1, '/');
+		if (slash) {
+			send_implied_dirs(f, flist, fbuf, fbuf+dlen+1, slash, flags, name_type);
+			continue;
+		}
+
+		if (name_type != NORMAL_NAME) {
+			STRUCT_STAT st;
+			if (link_stat(fbuf, &st, 1) != 0) {
+				io_error |= IOERR_GENERAL;
+				rsyserr(FERROR_XFER, errno, "link_stat %s failed",
+					full_fname(fbuf));
+				continue;
+			}
+			send_file_name(f, flist, fbuf, &st, FLAG_TOP_DIR | flags, ALL_FILTERS);
+		} else
+			send_file_name(f, flist, fbuf, NULL, FLAG_TOP_DIR | flags, ALL_FILTERS);
 	}
+
+	free(relname_list);
+}
+
+void send_extra_file_list(int f, int at_least)
+{
+	struct file_list *flist;
+	int64 start_write;
+	uint16 prev_flags;
+	int old_cnt, save_io_error = io_error;
+
+	if (flist_eof)
+		return;
+
+	/* Keep sending data until we have the requested number of
+	 * files in the upcoming file-lists. */
+	old_cnt = cur_flist->used;
+	for (flist = first_flist; flist != cur_flist; flist = flist->next)
+		old_cnt += flist->used;
+	while (file_total - old_cnt < at_least) {
+		struct file_struct *file = dir_flist->sorted[send_dir_ndx];
+		int dir_ndx, dstart = dir_count;
+		const char *pathname = F_PATHNAME(file);
+		int32 *dp;
+
+		flist = flist_new(0, "send_extra_file_list");
+		start_write = stats.total_written;
+
+		if (unsort_ndx)
+			dir_ndx = F_NDX(file);
+		else
+			dir_ndx = send_dir_ndx;
+		write_ndx(f, NDX_FLIST_OFFSET - dir_ndx);
+		flist->parent_ndx = dir_ndx;
+
+		send1extra(f, file, flist);
+		prev_flags = file->flags;
+		dp = F_DIR_NODE_P(file);
+
+		/* If there are any duplicate directory names that follow, we
+		 * send all the dirs together in one file-list.  The dir_flist
+		 * tree links all the child subdirs onto the last dup dir. */
+		while ((dir_ndx = DIR_NEXT_SIBLING(dp)) >= 0
+		    && dir_flist->sorted[dir_ndx]->flags & FLAG_DUPLICATE) {
+			send_dir_ndx = dir_ndx;
+			file = dir_flist->sorted[dir_ndx];
+			/* Try to avoid some duplicate scanning of identical dirs. */
+			if (F_PATHNAME(file) == pathname && prev_flags & FLAG_CONTENT_DIR)
+				file->flags &= ~FLAG_CONTENT_DIR;
+			send1extra(f, file, flist);
+			prev_flags = file->flags;
+			dp = F_DIR_NODE_P(file);
+		}
+
+		write_byte(f, 0);
+
+		if (need_unsorted_flist) {
+			if (!(flist->sorted = new_array(struct file_struct *, flist->used)))
+				out_of_memory("send_extra_file_list");
+			memcpy(flist->sorted, flist->files,
+			       flist->used * sizeof (struct file_struct*));
+		} else
+			flist->sorted = flist->files;
+
+		flist_sort_and_clean(flist, 0);
+
+		add_dirs_to_tree(send_dir_ndx, flist, dir_count - dstart);
+		flist_done_allocating(flist);
+
+		file_total += flist->used;
+		stats.flist_size += stats.total_written - start_write;
+		stats.num_files += flist->used;
+		if (verbose > 3)
+			output_flist(flist);
+
+		if (DIR_FIRST_CHILD(dp) >= 0) {
+			send_dir_ndx = DIR_FIRST_CHILD(dp);
+			send_dir_depth++;
+		} else {
+			while (DIR_NEXT_SIBLING(dp) < 0) {
+				if ((send_dir_ndx = DIR_PARENT(dp)) < 0) {
+					write_ndx(f, NDX_FLIST_EOF);
+					flist_eof = 1;
+					change_local_filter_dir(NULL, 0, 0);
+					goto finish;
+				}
+				send_dir_depth--;
+				file = dir_flist->sorted[send_dir_ndx];
+				dp = F_DIR_NODE_P(file);
+			}
+			send_dir_ndx = DIR_NEXT_SIBLING(dp);
+		}
+	}
+
+  finish:
+	if (io_error != save_io_error && !ignore_errors)
+		send_msg_int(MSG_IO_ERROR, io_error);
 }
 
 struct file_list *send_file_list(int f, int argc, char *argv[])
 {
-	int len;
+	static const char *lastdir;
+	static int lastdir_len = -1;
+	int len, dirlen;
 	STRUCT_STAT st;
-	char *p, *dir, olddir[sizeof curr_dir];
-	char lastpath[MAXPATHLEN] = "";
+	char *p, *dir;
 	struct file_list *flist;
 	struct timeval start_tv, end_tv;
 	int64 start_write;
 	int use_ff_fd = 0;
+	int disable_buffering;
+	int flags = recurse ? FLAG_CONTENT_DIR : 0;
+	int reading_remotely = filesfrom_host != NULL;
+	int rl_flags = (reading_remotely ? 0 : RL_DUMP_COMMENTS)
+#ifdef ICONV_OPTION
+		     | (filesfrom_convert ? RL_CONVERT : 0)
+#endif
+		     | (eol_nulls || reading_remotely ? RL_EOL_NULLS : 0);
 
 	rprintf(FLOG, "building file list\n");
 	if (show_filelist_p())
 		start_filelist_progress("building file list");
+	else if (inc_recurse && verbose && !am_server)
+		rprintf(FCLIENT, "sending incremental file list\n");
 
 	start_write = stats.total_written;
 	gettimeofday(&start_tv, NULL);
 
-	flist = flist_new(WITH_HLINK, "send_file_list");
+	if (relative_paths && protocol_version >= 30)
+		implied_dirs = 1; /* We send flagged implied dirs */
+
+#ifdef SUPPORT_HARD_LINKS
+	if (preserve_hard_links && protocol_version >= 30 && !cur_flist)
+		init_hard_links();
+#endif
+
+	flist = cur_flist = flist_new(0, "send_file_list");
+	if (inc_recurse) {
+		dir_flist = flist_new(FLIST_TEMP, "send_file_list");
+		flags |= FLAG_DIVERT_DIRS;
+	} else
+		dir_flist = cur_flist;
 
-	io_start_buffering_out();
+	disable_buffering = io_start_buffering_out(f);
 	if (filesfrom_fd >= 0) {
 		if (argv[0] && !push_dir(argv[0], 0)) {
-			rsyserr(FERROR, errno, "push_dir %s failed",
-				full_fname(argv[0]));
+			rsyserr(FERROR_XFER, errno, "push_dir %s failed in %s",
+				full_fname(argv[0]), curr_dir);
 			exit_cleanup(RERR_FILESELECT);
 		}
 		use_ff_fd = 1;
 	}
 
 	while (1) {
-		char fbuf[MAXPATHLEN];
-		char *fn;
-		int is_dot_dir;
+		char fbuf[MAXPATHLEN], *fn, name_type;
 
 		if (use_ff_fd) {
-			if (read_filesfrom_line(filesfrom_fd, fbuf) == 0)
+			if (read_line(filesfrom_fd, fbuf, sizeof fbuf, rl_flags) == 0)
 				break;
-			sanitize_path(fbuf, fbuf, "", 0, NULL);
+			sanitize_path(fbuf, fbuf, "", 0);
 		} else {
 			if (argc-- == 0)
 				break;
 			strlcpy(fbuf, *argv++, MAXPATHLEN);
 			if (sanitize_paths)
-				sanitize_path(fbuf, fbuf, "", 0, NULL);
+				sanitize_path(fbuf, fbuf, "", 0);
 		}
 
 		len = strlen(fbuf);
 		if (relative_paths) {
 			/* We clean up fbuf below. */
-			is_dot_dir = 0;
+			name_type = NORMAL_NAME;
 		} else if (!len || fbuf[len - 1] == '/') {
 			if (len == 2 && fbuf[0] == '.') {
 				/* Turn "./" into just "." rather than "./." */
-				fbuf[1] = '\0';
+				fbuf[--len] = '\0';
 			} else {
 				if (len + 1 >= MAXPATHLEN)
 					overflow_exit("send_file_list");
 				fbuf[len++] = '.';
 				fbuf[len] = '\0';
 			}
-			is_dot_dir = 1;
+			name_type = DOT_NAME;
 		} else if (len > 1 && fbuf[len-1] == '.' && fbuf[len-2] == '.'
 		    && (len == 2 || fbuf[len-3] == '/')) {
 			if (len + 2 >= MAXPATHLEN)
 				overflow_exit("send_file_list");
 			fbuf[len++] = '/';
 			fbuf[len++] = '.';
 			fbuf[len] = '\0';
-			is_dot_dir = 1;
-		} else {
-			is_dot_dir = fbuf[len-1] == '.'
-				   && (len == 1 || fbuf[len-2] == '/');
-		}
-
-		if (link_stat(fbuf, &st, copy_dirlinks) != 0) {
-			io_error |= IOERR_GENERAL;
-			rsyserr(FERROR, errno, "link_stat %s failed",
-				full_fname(fbuf));
-			continue;
-		}
-
-		if (S_ISDIR(st.st_mode) && !xfer_dirs) {
-			rprintf(FINFO, "skipping directory %s\n", fbuf);
-			continue;
-		}
+			name_type = DOT_NAME;
+		} else if (fbuf[len-1] == '.' && (len == 1 || fbuf[len-2] == '/'))
+			name_type = DOT_NAME;
+		else
+			name_type = NORMAL_NAME;
 
 		dir = NULL;
-		olddir[0] = '\0';
 
 		if (!relative_paths) {
 			p = strrchr(fbuf, '/');
 			if (p) {
 				*p = '\0';
 				if (p == fbuf)
