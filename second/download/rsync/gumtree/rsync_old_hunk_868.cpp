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

struct file_list *recv_file_list(int f)
{
	struct file_list *flist;
	unsigned short flags;
	int64 start_read;

	rprintf(FLOG, "receiving file list\n");
	if (show_filelist_p())
		start_filelist_progress("receiving file list");

	start_read = stats.total_read;

	flist = flist_new(WITH_HLINK, "recv_file_list");

	flist->count = 0;
	flist->malloced = 1000;
	flist->files = new_array(struct file_struct *, flist->malloced);
	if (!flist->files)
		goto oom;

	while ((flags = read_byte(f)) != 0) {
		struct file_struct *file;

		flist_expand(flist);

		if (protocol_version >= 28 && (flags & XMIT_EXTENDED_FLAGS))
			flags |= read_byte(f) << 8;
		file = receive_file_entry(flist, flags, f);

		if (S_ISREG(file->mode) || S_ISLNK(file->mode))
			stats.total_size += file->length;

		flist->files[flist->count++] = file;

		maybe_emit_filelist_progress(flist->count);

		if (verbose > 2) {
			rprintf(FINFO, "recv_file_name(%s)\n",
				f_name(file, NULL));
		}
	}
	receive_file_entry(NULL, 0, 0); /* Signal that we're done. */

	if (verbose > 2)
		rprintf(FINFO, "received %d names\n", flist->count);

	if (show_filelist_p())
		finish_filelist_progress(flist);

	clean_flist(flist, relative_paths, 1);

	if (f >= 0) {
		recv_uid_list(f, flist);

		/* Recv the io_error flag */
		if (lp_ignore_errors(module_id) || ignore_errors)
			read_int(f);
		else
			io_error |= read_int(f);
	}

	if (verbose > 3)
		output_flist(flist);

	if (list_only) {
		int i;
		for (i = 0; i < flist->count; i++)
			list_file_entry(flist->files[i]);
	}

	if (verbose > 2)
		rprintf(FINFO, "recv_file_list done\n");

	stats.flist_size = stats.total_read - start_read;
	stats.num_files = flist->count;

	return flist;

  oom:
	out_of_memory("recv_file_list");
	return NULL;		/* not reached */
}

static int file_compare(struct file_struct **file1, struct file_struct **file2)
{
	return f_name_cmp(*file1, *file2);
}

/* Search for an identically-named item in the file list.  Note that the
 * items must agree in their directory-ness, or no match is returned. */
int flist_find(struct file_list *flist, struct file_struct *f)
{
	int low = flist->low, high = flist->high;
	int diff, mid, mid_up;

	while (low <= high) {
		mid = (low + high) / 2;
		if (flist->files[mid]->basename)
			mid_up = mid;
		else {
			/* Scan for the next non-empty entry using the cached
			 * distance values.  If the value isn't fully up-to-
			 * date, update it. */
			mid_up = mid + flist->files[mid]->dir.depth;
			if (!flist->files[mid_up]->basename) {
				do {
				    mid_up += flist->files[mid_up]->dir.depth;
				} while (!flist->files[mid_up]->basename);
				flist->files[mid]->dir.depth = mid_up - mid;
			}
			if (mid_up > high) {
				/* If there's nothing left above us, set high to
				 * a non-empty entry below us and continue. */
				high = mid - flist->files[mid]->length;
				if (!flist->files[high]->basename) {
					do {
					    high -= flist->files[high]->length;
					} while (!flist->files[high]->basename);
					flist->files[mid]->length = mid - high;
				}
				continue;
			}
		}
		diff = f_name_cmp(flist->files[mid_up], f);
		if (diff == 0) {
			if (protocol_version < 29
			    && S_ISDIR(flist->files[mid_up]->mode)
			    != S_ISDIR(f->mode))
				return -1;
			return mid_up;
		}
		if (diff < 0)
			low = mid_up + 1;
