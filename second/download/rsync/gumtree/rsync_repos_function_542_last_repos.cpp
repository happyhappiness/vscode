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
	int disable_buffering, reenable_multiplex = -1;
	int flags = recurse ? FLAG_CONTENT_DIR : 0;
	int reading_remotely = filesfrom_host != NULL;
	int rl_flags = (reading_remotely ? 0 : RL_DUMP_COMMENTS)
#ifdef ICONV_OPTION
		     | (filesfrom_convert ? RL_CONVERT : 0)
#endif
		     | (eol_nulls || reading_remotely ? RL_EOL_NULLS : 0);
	int implied_dot_dir = 0;

	rprintf(FLOG, "building file list\n");
	if (show_filelist_p())
		start_filelist_progress("building file list");
	else if (inc_recurse && INFO_GTE(FLIST, 1) && !am_server)
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
		if (argv[0] && !change_dir(argv[0], CD_NORMAL)) {
			rsyserr(FERROR_XFER, errno, "change_dir %s failed",
				full_fname(argv[0]));
			exit_cleanup(RERR_FILESELECT);
		}
		if (protocol_version < 31) {
			/* Older protocols send the files-from data w/o packaging
			 * it in multiplexed I/O packets, so temporarily switch
			 * to buffered I/O to match this behavior. */
			reenable_multiplex = io_end_multiplex_in(MPLX_TO_BUFFERED);
		}
		use_ff_fd = 1;
	}

	if (!orig_dir)
		orig_dir = strdup(curr_dir);

	while (1) {
		char fbuf[MAXPATHLEN], *fn, name_type;

		if (use_ff_fd) {
			if (read_line(filesfrom_fd, fbuf, sizeof fbuf, rl_flags) == 0)
				break;
			sanitize_path(fbuf, fbuf, "", 0, SP_KEEP_DOT_DIRS);
		} else {
			if (argc-- == 0)
				break;
			strlcpy(fbuf, *argv++, MAXPATHLEN);
			if (sanitize_paths)
				sanitize_path(fbuf, fbuf, "", 0, SP_KEEP_DOT_DIRS);
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
			name_type = DOTDIR_NAME;
		} else if (len > 1 && fbuf[len-1] == '.' && fbuf[len-2] == '.'
		    && (len == 2 || fbuf[len-3] == '/')) {
			if (len + 2 >= MAXPATHLEN)
				overflow_exit("send_file_list");
			fbuf[len++] = '/';
			fbuf[len++] = '.';
			fbuf[len] = '\0';
			name_type = DOTDIR_NAME;
		} else if (fbuf[len-1] == '.' && (len == 1 || fbuf[len-2] == '/'))
			name_type = DOTDIR_NAME;
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
				else {
					dir = fbuf;
					clean_fname(dir, 0);
				}
				fn = p + 3;
				while (*fn == '/')
					fn++;
				if (!*fn)
					*--fn = '\0'; /* ensure room for '.' */
			} else
				fn = fbuf;
			/* A leading ./ can be used in relative mode to affect
			 * the dest dir without its name being in the path. */
			if (*fn == '.' && fn[1] == '/' && fn[2] && !implied_dot_dir)
				implied_dot_dir = -1;
			len = clean_fname(fn, CFN_KEEP_TRAILING_SLASH
					    | CFN_DROP_TRAILING_DOT_DIR);
			if (len == 1) {
				if (fn[0] == '/') {
					fn = "/.";
					len = 2;
					name_type = DOTDIR_NAME;
				} else if (fn[0] == '.')
					name_type = DOTDIR_NAME;
			} else if (fn[len-1] == '/') {
				fn[--len] = '\0';
				if (len == 1 && *fn == '.')
					name_type = DOTDIR_NAME;
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
			name_type = DOTDIR_NAME;
		}

		dirlen = dir ? strlen(dir) : 0;
		if (dirlen != lastdir_len || memcmp(lastdir, dir, dirlen) != 0) {
			if (!change_pathname(NULL, dir, -dirlen))
				goto bad_path;
			lastdir = pathname;
			lastdir_len = pathname_len;
		} else if (!change_pathname(NULL, lastdir, lastdir_len)) {
		    bad_path:
			if (implied_dot_dir < 0)
				implied_dot_dir = 0;
			continue;
		}

		if (implied_dot_dir < 0) {
			implied_dot_dir = 1;
			send_file_name(f, flist, ".", NULL, (flags | FLAG_IMPLIED_DIR) & ~FLAG_CONTENT_DIR, ALL_FILTERS);
		}

		if (fn != fbuf)
			memmove(fbuf, fn, len + 1);

		if (link_stat(fbuf, &st, copy_dirlinks || name_type != NORMAL_NAME) != 0
		 || (name_type != DOTDIR_NAME && is_daemon_excluded(fbuf, S_ISDIR(st.st_mode)))
		 || (relative_paths && path_is_daemon_excluded(fbuf, 1))) {
			if (errno != ENOENT || missing_args == 0) {
				/* This is a transfer error, but inhibit deletion
				 * only if we might be omitting an existing file. */
				if (errno != ENOENT)
					io_error |= IOERR_GENERAL;
				rsyserr(FERROR_XFER, errno, "link_stat %s failed",
					full_fname(fbuf));
				continue;
			} else if (missing_args == 1) {
				/* Just ignore the arg. */
				continue;
			} else /* (missing_args == 2) */ {
				/* Send the arg as a "missing" entry with
				 * mode 0, which tells the generator to delete it. */
				memset(&st, 0, sizeof st);
			}
		}

		/* A dot-dir should not be excluded! */
		if (name_type != DOTDIR_NAME && st.st_mode != 0
		 && is_excluded(fbuf, S_ISDIR(st.st_mode) != 0, ALL_FILTERS))
			continue;

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
				send_implied_dirs(f, flist, fbuf, fbuf, p, flags,
						  IS_MISSING_FILE(st) ? MISSING_NAME : name_type);
				if (fn == p)
					continue;
			}
		} else if (implied_dirs && (p=strrchr(fbuf,'/')) && p != fbuf) {
			/* Send the implied directories at the start of the
			 * source spec, so we get their permissions right. */
			send_implied_dirs(f, flist, fbuf, fbuf, p, flags, 0);
		}

		if (one_file_system)
			filesystem_dev = st.st_dev;

		if (recurse || (xfer_dirs && name_type != NORMAL_NAME)) {
			struct file_struct *file;
			file = send_file_name(f, flist, fbuf, &st,
					      FLAG_TOP_DIR | FLAG_CONTENT_DIR | flags,
					      NO_FILTERS);
			if (!file)
				continue;
			if (inc_recurse) {
				if (name_type == DOTDIR_NAME) {
					if (send_dir_depth < 0) {
						send_dir_depth = 0;
						change_local_filter_dir(fbuf, len, send_dir_depth);
					}
					send_directory(f, flist, fbuf, len, flags);
				}
			} else
				send_if_directory(f, flist, file, fbuf, len, flags);
		} else
			send_file_name(f, flist, fbuf, &st, flags, NO_FILTERS);
	}

	if (reenable_multiplex >= 0)
		io_start_multiplex_in(reenable_multiplex);

	gettimeofday(&end_tv, NULL);
	stats.flist_buildtime = (int64)(end_tv.tv_sec - start_tv.tv_sec) * 1000
			      + (end_tv.tv_usec - start_tv.tv_usec) / 1000;
	if (stats.flist_buildtime == 0)
		stats.flist_buildtime = 1;
	start_tv = end_tv;

	/* Indicate end of file list */
	if (io_error == 0 || ignore_errors)
		write_byte(f, 0);
	else if (use_safe_inc_flist) {
		write_shortint(f, XMIT_EXTENDED_FLAGS|XMIT_IO_ERROR_ENDLIST);
		write_varint(f, io_error);
	} else {
		if (delete_during && inc_recurse)
			fatal_unsafe_io_error();
		write_byte(f, 0);
	}

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
	file_old_total += flist->used;

	if (numeric_ids <= 0 && !inc_recurse)
		send_id_list(f);

	/* send the io_error flag */
	if (protocol_version < 30)
		write_int(f, ignore_errors ? 0 : io_error);
	else if (!use_safe_inc_flist && io_error && !ignore_errors)
		send_msg_int(MSG_IO_ERROR, io_error);

	if (disable_buffering)
		io_end_buffering_out(IOBUF_FREE_BUFS);

	stats.flist_size = stats.total_written - start_write;
	stats.num_files = flist->used;

	if (DEBUG_GTE(FLIST, 3))
		output_flist(flist);

	if (DEBUG_GTE(FLIST, 2))
		rprintf(FINFO, "send_file_list done\n");

	if (inc_recurse) {
		send_dir_depth = 1;
		add_dirs_to_tree(-1, flist, stats.num_dirs);
		if (!file_total || strcmp(flist->sorted[flist->low]->basename, ".") != 0)
			flist->parent_ndx = -1;
		flist_done_allocating(flist);
		if (send_dir_ndx < 0) {
			write_ndx(f, NDX_FLIST_EOF);
			flist_eof = 1;
			if (DEBUG_GTE(FLIST, 3))
				rprintf(FINFO, "[%s] flist_eof=1\n", who_am_i());
		}
		else if (file_total == 1) {
			/* If we're creating incremental file-lists and there
			 * was just 1 item in the first file-list, send 1 more
			 * file-list to check if this is a 1-file xfer. */
			send_extra_file_list(f, 1);
		}
	} else {
		flist_eof = 1;
		if (DEBUG_GTE(FLIST, 3))
			rprintf(FINFO, "[%s] flist_eof=1\n", who_am_i());
	}

	return flist;
}