struct file_list *send_file_list(int f, int argc, char *argv[])
{
	int l;
	STRUCT_STAT st;
	char *p, *dir, olddir[sizeof curr_dir];
	char lastpath[MAXPATHLEN] = "";
	struct file_list *flist;
	struct timeval start_tv, end_tv;
	int64 start_write;
	int use_ff_fd = 0;

	if (show_filelist_p())
		start_filelist_progress("building file list");

	start_write = stats.total_written;
	gettimeofday(&start_tv, NULL);

	flist = flist_new(WITH_HLINK, "send_file_list");

	io_start_buffering_out();
	if (filesfrom_fd >= 0) {
		if (argv[0] && !push_dir(argv[0])) {
			rsyserr(FERROR, errno, "push_dir %s failed",
				full_fname(argv[0]));
			exit_cleanup(RERR_FILESELECT);
		}
		use_ff_fd = 1;
	}

	while (1) {
		struct file_struct *file;
		char fname2[MAXPATHLEN];
		char *fname = fname2;
		int is_dot_dir;

		if (use_ff_fd) {
			if (read_filesfrom_line(filesfrom_fd, fname) == 0)
				break;
			sanitize_path(fname, fname, "", 0);
		} else {
			if (argc-- == 0)
				break;
			strlcpy(fname, *argv++, MAXPATHLEN);
			if (sanitize_paths)
				sanitize_path(fname, fname, "", 0);
		}

		l = strlen(fname);
		if (!l || fname[l - 1] == '/') {
			if (l == 2 && fname[0] == '.') {
				/* Turn "./" into just "." rather than "./." */
				fname[1] = '\0';
			} else {
				if (l + 1 >= MAXPATHLEN)
					overflow_exit("send_file_list");
				fname[l++] = '.';
				fname[l] = '\0';
			}
			is_dot_dir = 1;
		} else if (l > 1 && fname[l-1] == '.' && fname[l-2] == '.'
		    && (l == 2 || fname[l-3] == '/')) {
			if (l + 2 >= MAXPATHLEN)
				overflow_exit("send_file_list");
			fname[l++] = '/';
			fname[l++] = '.';
			fname[l] = '\0';
			is_dot_dir = 1;
		} else {
			is_dot_dir = fname[l-1] == '.'
				   && (l == 1 || fname[l-2] == '/');
		}

		if (link_stat(fname, &st, keep_dirlinks) != 0) {
			io_error |= IOERR_GENERAL;
			rsyserr(FERROR, errno, "link_stat %s failed",
				full_fname(fname));
			continue;
		}

		if (S_ISDIR(st.st_mode) && !xfer_dirs) {
			rprintf(FINFO, "skipping directory %s\n",
				safe_fname(fname));
			continue;
		}

		dir = NULL;
		olddir[0] = '\0';

		if (!relative_paths) {
			p = strrchr(fname, '/');
			if (p) {
				*p = 0;
				if (p == fname)
					dir = "/";
				else
					dir = fname;
				fname = p + 1;
			}
		} else if (implied_dirs && (p=strrchr(fname,'/')) && p != fname) {
			/* this ensures we send the intermediate directories,
			   thus getting their permissions right */
			char *lp = lastpath, *fn = fname, *slash = fname;
			*p = 0;
			/* Skip any initial directories in our path that we
			 * have in common with lastpath. */
			while (*fn && *lp == *fn) {
				if (*fn == '/')
					slash = fn;
				lp++, fn++;
			}
			*p = '/';
			if (fn != p || (*lp && *lp != '/')) {
				int save_copy_links = copy_links;
				int save_xfer_dirs = xfer_dirs;
				copy_links = copy_unsafe_links;
				xfer_dirs = 1;
				while ((slash = strchr(slash+1, '/')) != 0) {
					*slash = 0;
					send_file_name(f, flist, fname, 0);
					*slash = '/';
				}
				copy_links = save_copy_links;
				xfer_dirs = save_xfer_dirs;
				*p = 0;
				strlcpy(lastpath, fname, sizeof lastpath);
				*p = '/';
			}
		}

		if (!*fname)
			fname = ".";

		if (dir && *dir) {
			static char *lastdir;
			static int lastdir_len;

			strcpy(olddir, curr_dir); /* can't overflow */

			if (!push_dir(dir)) {
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

		if (one_file_system)
			filesystem_dev = st.st_dev;

		if ((file = send_file_name(f, flist, fname, XMIT_TOP_DIR))) {
			if (recurse || (xfer_dirs && is_dot_dir))
				send_if_directory(f, flist, file);
		}

		if (olddir[0]) {
			flist_dir = NULL;
			flist_dir_len = 0;
			if (!pop_dir(olddir)) {
				rsyserr(FERROR, errno, "pop_dir %s failed",
					full_fname(dir));
				exit_cleanup(RERR_FILESELECT);
			}
		}
	}

	gettimeofday(&end_tv, NULL);
	stats.flist_buildtime = (i