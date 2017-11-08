struct file_list *send_file_list(int f, int argc, char *argv[])
{
	int len;
	STRUCT_STAT st;
	char *p, *dir, olddir[sizeof curr_dir];
	char lastpath[MAXPATHLEN] = "";
	struct file_list *flist;
	struct timeval start_tv, end_tv;
	int64 start_write;
	int use_ff_fd = 0;

	rprintf(FLOG, "building file list\n");
	if (show_filelist_p())
		start_filelist_progress("building file list");

	start_write = stats.total_written;
	gettimeofday(&start_tv, NULL);

	flist = flist_new(WITH_HLINK, "send_file_list");

	io_start_buffering_out();
	if (filesfrom_fd >= 0) {
		if (argv[0] && !push_dir(argv[0], 0)) {
			rsyserr(FERROR, errno, "push_dir %s failed",
				full_fname(argv[0]));
			exit_cleanup(RERR_FILESELECT);
		}
		use_ff_fd = 1;
	}

	while (1) {
		char fbuf[MAXPATHLEN];
		char *fn;
		int is_dot_dir;

		if (use_ff_fd) {
			if (read_filesfrom_line(filesfrom_fd, fbuf) == 0)
				break;
			sanitize_path(fbuf, fbuf, "", 0, NULL);
		} else {
			if (argc-- == 0)
				break;
			strlcpy(fbuf, *argv++, MAXPATHLEN);
			if (sanitize_paths)
				sanitize_path(fbuf, fbuf, "", 0, NULL);
		}

		len = strlen(fbuf);
		if (relative_paths) {
			/* We clean up fbuf below. */
			is_dot_dir = 0;
		} else if (!len || fbuf[len - 1] == '/') {
			if (len == 2 && fbuf[0] == '.') {
				/* Turn "./" into just "." rather than "./." */
				fbuf[1] = '\0';
			} else {
				if (len + 1 >= MAXPATHLEN)
					overflow_exit("send_file_list");
				fbuf[len++] = '.';
				fbuf[len] = '\0';
			}
			is_dot_dir = 1;
		} else if (len > 1 && fbuf[len-1] == '.' && fbuf[len-2] == '.'
		    && (len == 2 || fbuf[len-3] == '/')) {
			if (len + 2 >= MAXPATHLEN)
				overflow_exit("send_file_list");
			fbuf[len++] = '/';
			fbuf[len++] = '.';
			fbuf[len] = '\0';
			is_dot_dir = 1;
		} else {
			is_dot_dir = fbuf[len-1] == '.'
				   && (len == 1 || fbuf[len-2] == '/');
		}

		if (link_stat(fbuf, &st, copy_dirlinks) != 0) {
			io_error |= IOERR_GENERAL;
			rsyserr(FERROR, errno, "link_stat %s failed",
				full_fname(fbuf));
			continue;
		}

		if (S_ISDIR(st.st_mode) && !xfer_dirs) {
			rprintf(FINFO, "skipping directory %s\n", fbuf);
			continue;
		}

		dir = NULL;
		olddir[0] = '\0';

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
				len -= p - fbuf + 3;
				fn = p + 3;
			} else
				fn = fbuf;
			/* Get rid of trailing "/" and "/.". */
			while (len) {
				if (fn[len - 1] == '/') {
					is_dot_dir = 1;
					if (!--len && !dir) {
						len++;
						break;
					}
				}
				else if (len >= 2 && fn[len - 1] == '.'
						  && fn[len - 2] == '/') {
					is_dot_dir = 1;
					if (!(len -= 2) && !dir) {
						len++;
						break;
					}
				} else
					break;
			}
			if (len == 1 && fn[0] == '/')
				fn[len++] = '.';
			fn[len] = '\0';
			/* Reject a ".." dir in the active part of the path. */
			for (p = fn; (p = strstr(p, "..")) != NULL; p += 2) {
				if ((p[2] == '/' || p[2] == '\0')
				 && (p == fn || p[-1] == '/')) {
					rprintf(FERROR,
					    "found \"..\" dir in relative path: %s\n",
					    fbuf);
					exit_cleanup(RERR_SYNTAX);
				}
			}
		}

		if (!*fn) {
			len = 1;
			fn = ".";
		}

		if (dir && *dir) {
			static char *lastdir;
			static int lastdir_len;

			strlcpy(olddir, curr_dir, sizeof olddir);

			if (!push_dir(dir, 0)) {
				io_error |= IOERR_GENERAL;
				rsyserr(FERROR, errno, "push_dir %s failed",
					full_fname(dir));
				continue;
			}

			if (lastdir && strcmp(lastdir, dir) == 0) {
				flist_dir = lastdir;
				flist_dir_len = lastdir_len;
			} else {
				flist_dir = lastdir = strdup(dir);
				flist_dir_len = lastdir_len = strlen(dir);
			}
		}

		if (fn != fbuf)
			memmove(fbuf, fn, len + 1);

		if (implied_dirs && (p=strrchr(fbuf,'/')) && p != fbuf) {
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
			if (fn != p || (*lp && *lp != '/')) {
				int save_copy_links = copy_links;
				int save_xfer_dirs = xfer_dirs;
				copy_links |= copy_unsafe_links;
				xfer_dirs = 1;
				while ((slash = strchr(slash+1, '/')) != 0) {
					*slash = '\0';
					send_file_name(f, flist, fbuf, NULL, 0);
					*slash = '/';
				}
				copy_links = save_copy_links;
				xfer_dirs = save_xfer_dirs;
				*p = '\0';
				strlcpy(lastpath, fbuf, sizeof lastpath);
				*p = '/';
			}
		}

		if (one_file_system)
			filesystem_dev = st.st_dev;

		if (recurse || (xfer_dirs && is_dot_dir)) {
			struct file_struct *file;
			file = send_file_name(f, flist, fbuf, &st, FLAG_TOP_DIR);
			if (file)
				send_if_directory(f, flist, file, fbuf, len);
		} else
			send_file_name(f, flist, fbuf, &st, 0);

		if (olddir[0]) {
			flist_dir = NULL;
			flist_dir_len = 0;
			if (!pop_dir(olddir)) {
				rsyserr(FERROR, errno, "pop_dir %s failed",
					full_fname(olddir));
				exit_cleanup(RERR_FILESELECT);
			}
		}
	}

	gettimeofday(&end_tv, NULL);
	stats.flist_buildtime = (int64)(end_tv.tv_sec - start_tv.tv_sec) * 1000
			      + (end_tv.tv_usec - start_tv.tv_usec) / 1000;
	if (stats.flist_buildtime == 0)
		stats.flist_buildtime = 1;
	start_tv = end_tv;

	send_file_entry(NULL, f);

	if (show_filelist_p())
		finish_filelist_progress(flist);

	gettimeofday(&end_tv, NULL);
	stats.flist_xfertime = (int64)(end_tv.tv_sec - start_tv.tv_sec) * 1000
			     + (end_tv.tv_usec - start_tv.tv_usec) / 1000;

	if (flist->hlink_pool) {
		pool_destroy(flist->hlink_pool);
		flist->hlink_pool = NULL;
	}

	/* Sort the list without removing any duplicates.  This allows the
	 * receiving side to ask for any name they like, which gives us the
	 * flexibility to change the way we unduplicate names in the future
	 * without causing a compatibility problem with older versions. */
	clean_flist(flist, 0, 0);

	send_uid_list(f);

	/* send the io_error flag */
	write_int(f, lp_ignore_errors(module_id) ? 0 : io_error);

	io_end_buffering();
	stats.flist_size = stats.total_written - start_write;
	stats.num_files = flist->count;

	if (verbose > 3)
		output_flist(flist);

	if (verbose > 2)
		rprintf(FINFO, "send_file_list done\n");

	return flist;
}