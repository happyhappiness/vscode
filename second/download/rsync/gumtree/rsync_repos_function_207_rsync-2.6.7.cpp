void generate_files(int f_out, struct file_list *flist, char *local_name)
{
	int i;
	char fbuf[MAXPATHLEN];
	int itemizing, maybe_ATTRS_REPORT;
	enum logcode code;
	int lull_mod = allowed_lull * 5;
	int need_retouch_dir_times = preserve_times && !omit_dir_times;
	int need_retouch_dir_perms = 0;
	int save_ignore_existing = ignore_existing;
	int save_ignore_non_existing = ignore_non_existing;
	int save_do_progress = do_progress;
	int save_make_backups = make_backups;
	int dir_tweaking = !(list_only || local_name || dry_run);

	if (protocol_version >= 29) {
		itemizing = 1;
		maybe_ATTRS_REPORT = log_format_has_i ? 0 : ATTRS_REPORT;
		code = daemon_log_format_has_i ? 0 : FLOG;
	} else if (am_daemon) {
		itemizing = daemon_log_format_has_i && do_xfers;
		maybe_ATTRS_REPORT = ATTRS_REPORT;
		code = itemizing || !do_xfers ? FCLIENT : FINFO;
	} else if (!am_server) {
		itemizing = log_format_has_i;
		maybe_ATTRS_REPORT = log_format_has_i ? 0 : ATTRS_REPORT;
		code = itemizing ? 0 : FINFO;
	} else {
		itemizing = 0;
		maybe_ATTRS_REPORT = ATTRS_REPORT;
		code = FINFO;
	}

	if (verbose > 2) {
		rprintf(FINFO, "generator starting pid=%ld count=%d\n",
			(long)getpid(), flist->count);
	}

	if (delete_before && !local_name && flist->count > 0)
		do_delete_pass(flist);
	do_progress = 0;

	if (append_mode || whole_file < 0)
		whole_file = 0;
	if (verbose >= 2) {
		rprintf(FINFO, "delta-transmission %s\n",
			whole_file
			? "disabled for local transfer or --whole-file"
			: "enabled");
	}

	/* Since we often fill up the outgoing socket and then just sit around
	 * waiting for the other 2 processes to do their thing, we don't want
	 * to exit on a timeout.  If the data stops flowing, the receiver will
	 * notice that and let us know via the redo pipe (or its closing). */
	ignore_timeout = 1;

	for (i = 0; i < flist->count; i++) {
		struct file_struct *file = flist->files[i];

		if (!file->basename)
			continue;

		if (local_name)
			strlcpy(fbuf, local_name, sizeof fbuf);
		else
			f_name(file, fbuf);
		recv_generator(fbuf, file, i, itemizing, maybe_ATTRS_REPORT,
			       code, f_out);

		/* We need to ensure that any dirs we create have writeable
		 * permissions during the time we are putting files within
		 * them.  This is then fixed after the transfer is done. */
#ifdef HAVE_CHMOD
		if (!am_root && S_ISDIR(file->mode) && !(file->mode & S_IWUSR)
		 && dir_tweaking) {
			mode_t mode = file->mode | S_IWUSR; /* user write */
			char *fname = local_name ? local_name : fbuf;
			if (do_chmod(fname, mode) < 0) {
				rsyserr(FERROR, errno,
					"failed to modify permissions on %s",
					full_fname(fname));
			}
			need_retouch_dir_perms = 1;
		}
#endif

		if (preserve_hard_links)
			check_for_finished_hlinks(itemizing, code);

		if (allowed_lull && !(i % lull_mod))
			maybe_send_keepalive();
		else if (!(i % 200))
			maybe_flush_socket();
	}
	recv_generator(NULL, NULL, 0, 0, 0, code, -1);
	if (delete_during)
		delete_in_dir(NULL, NULL, NULL, NULL);

	phase++;
	csum_length = SUM_LENGTH;
	max_size = min_size = ignore_existing = ignore_non_existing = 0;
	update_only = always_checksum = size_only = 0;
	ignore_times = 1;
	if (append_mode)  /* resend w/o append mode */
		append_mode = -1; /* ... but only longer files */
	make_backups = 0; /* avoid a duplicate backup for inplace processing */

	if (verbose > 2)
		rprintf(FINFO,"generate_files phase=%d\n",phase);

	write_int(f_out, -1);

	/* files can cycle through the system more than once
	 * to catch initial checksum errors */
	while ((i = get_redo_num(itemizing, code)) != -1) {
		struct file_struct *file = flist->files[i];
		if (local_name)
			strlcpy(fbuf, local_name, sizeof fbuf);
		else
			f_name(file, fbuf);
		recv_generator(fbuf, file, i, itemizing, maybe_ATTRS_REPORT,
			       code, f_out);
	}

	phase++;
	ignore_non_existing = save_ignore_non_existing;
	ignore_existing = save_ignore_existing;
	make_backups = save_make_backups;

	if (verbose > 2)
		rprintf(FINFO,"generate_files phase=%d\n",phase);

	write_int(f_out, -1);
	/* Reduce round-trip lag-time for a useless delay-updates phase. */
	if (protocol_version >= 29 && !delay_updates)
		write_int(f_out, -1);

	/* Read MSG_DONE for the redo phase (and any prior messages). */
	get_redo_num(itemizing, code);

	if (protocol_version >= 29) {
		phase++;
		if (verbose > 2)
			rprintf(FINFO, "generate_files phase=%d\n", phase);
		if (delay_updates)
			write_int(f_out, -1);
		/* Read MSG_DONE for delay-updates phase & prior messages. */
		get_redo_num(itemizing, code);
	}

	do_progress = save_do_progress;
	if (delete_after && !local_name && flist->count > 0)
		do_delete_pass(flist);

	if ((need_retouch_dir_perms || need_retouch_dir_times) && dir_tweaking) {
		int j = 0;
		/* Now we need to fix any directory permissions that were
		 * modified during the transfer and/or re-set any tweaked
		 * modified-time values. */
		for (i = 0; i < flist->count; i++) {
			struct file_struct *file = flist->files[i];

			if (!file->basename || !S_ISDIR(file->mode))
				continue;
			if (!need_retouch_dir_times && file->mode & S_IWUSR)
				continue;
			recv_generator(f_name(file, NULL), file, i, itemizing,
				       maybe_ATTRS_REPORT, code, -1);
			if (allowed_lull && !(++j % lull_mod))
				maybe_send_keepalive();
			else if (!(j % 200))
				maybe_flush_socket();
		}
	}
	recv_generator(NULL, NULL, 0, 0, 0, code, -1);

	if (max_delete > 0 && deletion_count > max_delete) {
		rprintf(FINFO,
			"Deletions stopped due to --max-delete limit (%d skipped)\n",
			deletion_count - max_delete);
		io_error |= IOERR_DEL_LIMIT;
	}

	if (verbose > 2)
		rprintf(FINFO,"generate_files finished\n");
}