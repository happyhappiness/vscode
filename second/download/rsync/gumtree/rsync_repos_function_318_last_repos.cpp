static void touch_up_dirs(struct file_list *flist, int ndx)
{
	static int counter = 0;
	struct file_struct *file;
	char *fname;
	BOOL fix_dir_perms;
	int i, start, end;

	if (ndx < 0) {
		start = 0;
		end = flist->used - 1;
	} else
		start = end = ndx;

	/* Fix any directory permissions that were modified during the
	 * transfer and/or re-set any tweaked modified-time values. */
	for (i = start; i <= end; i++, counter++) {
		file = flist->files[i];
		if (!F_IS_ACTIVE(file))
			continue;
		if (!S_ISDIR(file->mode)
		 || (!implied_dirs && file->flags & FLAG_IMPLIED_DIR))
			continue;
		if (DEBUG_GTE(TIME, 2)) {
			fname = f_name(file, NULL);
			rprintf(FINFO, "touch_up_dirs: %s (%d)\n",
				NS(fname), i);
		}
		/* Be sure not to retouch permissions with --fake-super. */
		fix_dir_perms = !am_root && !(file->mode & S_IWUSR);
		if (file->flags & FLAG_MISSING_DIR || !(need_retouch_dir_times || fix_dir_perms))
			continue;
		fname = f_name(file, NULL);
		if (fix_dir_perms)
			do_chmod(fname, file->mode);
		if (need_retouch_dir_times) {
			STRUCT_STAT st;
			if (link_stat(fname, &st, 0) == 0
			 && cmp_time(st.st_mtime, file->modtime) != 0)
				set_modtime(fname, file->modtime, F_MOD_NSEC(file), file->mode);
		}
		if (counter >= loopchk_limit) {
			if (allowed_lull)
				maybe_send_keepalive(time(NULL), MSK_ALLOW_FLUSH);
			else
				maybe_flush_socket(0);
			counter = 0;
		}
	}
}