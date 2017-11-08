struct file_list *send_file_list(int f, int argc, char *argv[])
{
	int l;
	STRUCT_STAT st;
	char *p, *dir, *olddir;
	char lastpath[MAXPATHLEN] = "";
	struct file_list *flist;
	int64 start_write;
	int use_ff_fd = 0;

	if (show_filelist_p() && f != -1)
		start_filelist_progress("building file list");

	start_write = stats.total_written;

	flist = flist_new();

	if (f != -1) {
		io_start_buffering(f);
		if (filesfrom_fd >= 0) {
			if (argv[0] && !push_dir(argv[0], 0)) {
				rprintf(FERROR, "push_dir %s failed: %s\n",
					full_fname(argv[0]), strerror(errno));
				exit_cleanup(RERR_FILESELECT);
			}
			use_ff_fd = 1;
		}
	}

	while (1) {
		char fname2[MAXPATHLEN];
		char *fname = fname2;

		if (use_ff_fd) {
			if (read_filesfrom_line(filesfrom_fd, fname) == 0)
				break;
			sanitize_path(fname, NULL);
		} else {
			if (argc-- == 0)
				break;
			strlcpy(fname, *argv++, MAXPATHLEN);
			if (sanitize_paths)
				sanitize_path(fname, NULL);
		}

		l = strlen(fname);
		if (fname[l - 1] == '/') {
			if (l == 2 && fname[0] == '.') {
				/* Turn "./" into just "." rather than "./." */
				fname[1] = '\0';
			} else {
				strlcat(fname, ".", MAXPATHLEN);
			}
		}

		if (link_stat(fname, &st) != 0) {
			if (f != -1) {
				io_error |= IOERR_GENERAL;
				rprintf(FERROR, "link_stat %s failed: %s\n",
					full_fname(fname), strerror(errno));
			}
			continue;
		}

		if (S_ISDIR(st.st_mode) && !recurse && !files_from) {
			rprintf(FINFO, "skipping directory %s\n", fname);
			continue;
		}

		dir = NULL;
		olddir = NULL;

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
		} else if (f != -1 && implied_dirs && (p=strrchr(fname,'/')) && p != fname) {
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
				int copy_links_saved = copy_links;
				int recurse_saved = recurse;
				copy_links = copy_unsafe_links;
				/* set recurse to 1 to prevent make_file
				 * from ignoring directory, but still
				 * turn off the recursive parameter to
				 * send_file_name */
				recurse = 1;
				while ((slash = strchr(slash+1, '/')) != 0) {
					*slash = 0;
					send_file_name(f, flist, fname, 0, 0);
					*slash = '/';
				}
				copy_links = copy_links_saved;
				recurse = recurse_saved;
				*p = 0;
				strlcpy(lastpath, fname, sizeof lastpath);
				*p = '/';
			}
		}

		if (!*fname)
			fname = ".";

		if (dir && *dir) {
			olddir = push_dir(dir, 1);

			if (!olddir) {
				io_error |= IOERR_GENERAL;
				rprintf(FERROR, "push_dir %s failed: %s\n",
					full_fname(dir), strerror(errno));
				continue;
			}

			flist_dir = dir;
		}

		if (one_file_system)
			set_filesystem(fname);

		send_file_name(f, flist, fname, recurse, FLAG_DELETE);

		if (olddir != NULL) {
			flist_dir = NULL;
			if (pop_dir(olddir) != 0) {
				rprintf(FERROR, "pop_dir %s failed: %s\n",
					full_fname(dir), strerror(errno));
				exit_cleanup(RERR_FILESELECT);
			}
		}
	}

	if (f != -1) {
		send_file_entry(NULL, f, 0);
	}

	if (show_filelist_p() && f != -1) {
		finish_filelist_progress(flist);
	}

	clean_flist(flist, 0, 0);

	/* now send the uid/gid list. This was introduced in protocol
	   version 15 */
	if (f != -1) {
		send_uid_list(f);
	}

	/* send the io_error flag */
	if (f != -1) {
		extern int module_id;
		write_int(f, lp_ignore_errors(module_id) ? 0 : io_error);
	}

	if (f != -1) {
		io_end_buffering();
		stats.flist_size = stats.total_written - start_write;
		stats.num_files = flist->count;
		if (write_batch)	/*  dw  */
			write_batch_flist_info(flist->count, flist->files);
	}

	if (verbose > 2)
		rprintf(FINFO, "send_file_list done\n");

	return flist;
}