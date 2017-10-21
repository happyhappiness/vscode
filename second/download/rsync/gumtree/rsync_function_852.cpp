void generate_files(int f_out, const char *local_name)
{
	int i, ndx;
	char fbuf[MAXPATHLEN];
	int itemizing;
	enum logcode code;
	int save_do_progress = do_progress;

	if (protocol_version >= 29) {
		itemizing = 1;
		maybe_ATTRS_REPORT = stdout_format_has_i ? 0 : ATTRS_REPORT;
		code = logfile_format_has_i ? FNONE : FLOG;
	} else if (am_daemon) {
		itemizing = logfile_format_has_i && do_xfers;
		maybe_ATTRS_REPORT = ATTRS_REPORT;
		code = itemizing || !do_xfers ? FCLIENT : FINFO;
	} else if (!am_server) {
		itemizing = stdout_format_has_i;
		maybe_ATTRS_REPORT = stdout_format_has_i ? 0 : ATTRS_REPORT;
		code = itemizing ? FNONE : FINFO;
	} else {
		itemizing = 0;
		maybe_ATTRS_REPORT = ATTRS_REPORT;
		code = FINFO;
	}
	solo_file = local_name;
	dir_tweaking = !(list_only || solo_file || dry_run);
	need_retouch_dir_times = preserve_times > 1;
	lull_mod = allowed_lull * 5;

	if (verbose > 2)
		rprintf(FINFO, "generator starting pid=%ld\n", (long)getpid());

	if (delete_before && !solo_file && cur_flist->used > 0)
		do_delete_pass();
	if (delete_during == 2) {
		deldelay_size = BIGPATHBUFLEN * 4;
		deldelay_buf = new_array(char, deldelay_size);
		if (!deldelay_buf)
			out_of_memory("delete-delay");
	}
	do_progress = 0;

	if (append_mode > 0 || whole_file < 0)
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

	dflt_perms = (ACCESSPERMS & ~orig_umask);

	do {
#ifdef SUPPORT_HARD_LINKS
		if (preserve_hard_links && inc_recurse) {
			while (!flist_eof && file_total < FILECNT_LOOKAHEAD/2)
				wait_for_receiver();
		}
#endif

		if (inc_recurse && cur_flist->parent_ndx >= 0) {
			struct file_struct *fp = dir_flist->files[cur_flist->parent_ndx];
			f_name(fp, fbuf);
			ndx = cur_flist->ndx_start - 1;
			recv_generator(fbuf, fp, ndx, itemizing, code, f_out);
			if (delete_during && dry_run < 2 && !list_only) {
				if (BITS_SETnUNSET(fp->flags, FLAG_CONTENT_DIR, FLAG_MISSING_DIR)) {
					dev_t dirdev;
					if (one_file_system) {
						uint32 *devp = F_DIR_DEV_P(fp);
						dirdev = MAKEDEV(DEV_MAJOR(devp), DEV_MINOR(devp));
					} else
						dirdev = MAKEDEV(0, 0);
					delete_in_dir(f_name(fp, fbuf), fp, &dirdev);
				}
			}
		}
		for (i = cur_flist->low; i <= cur_flist->high; i++) {
			struct file_struct *file = cur_flist->sorted[i];

			if (!F_IS_ACTIVE(file))
				continue;

			if (unsort_ndx)
				ndx = F_NDX(file);
			else
				ndx = i + cur_flist->ndx_start;

			if (solo_file)
				strlcpy(fbuf, solo_file, sizeof fbuf);
			else
				f_name(file, fbuf);
			recv_generator(fbuf, file, ndx, itemizing, code, f_out);

			check_for_finished_files(itemizing, code, 0);

			if (allowed_lull && !(i % lull_mod))
				maybe_send_keepalive();
			else if (!(i & 0xFF))
				maybe_flush_socket(0);
		}

		if (!inc_recurse) {
			write_ndx(f_out, NDX_DONE);
			break;
		}

		while (1) {
			check_for_finished_files(itemizing, code, 1);
			if (cur_flist->next || flist_eof)
				break;
			wait_for_receiver();
		}
	} while ((cur_flist = cur_flist->next) != NULL);

	if (delete_during)
		delete_in_dir(NULL, NULL, &dev_zero);
	phase++;
	if (verbose > 2)
		rprintf(FINFO, "generate_files phase=%d\n", phase);

	while (1) {
		check_for_finished_files(itemizing, code, 1);
		if (msgdone_cnt)
			break;
		wait_for_receiver();
	}

	phase++;
	if (verbose > 2)
		rprintf(FINFO, "generate_files phase=%d\n", phase);

	write_ndx(f_out, NDX_DONE);
	/* Reduce round-trip lag-time for a useless delay-updates phase. */
	if (protocol_version >= 29 && !delay_updates)
		write_ndx(f_out, NDX_DONE);

	/* Read MSG_DONE for the redo phase (and any prior messages). */
	while (1) {
		check_for_finished_files(itemizing, code, 0);
		if (msgdone_cnt > 1)
			break;
		wait_for_receiver();
	}

	if (protocol_version >= 29) {
		phase++;
		if (verbose > 2)
			rprintf(FINFO, "generate_files phase=%d\n", phase);
		if (delay_updates)
			write_ndx(f_out, NDX_DONE);
		/* Read MSG_DONE for delay-updates phase & prior messages. */
		while (msgdone_cnt == 2)
			wait_for_receiver();
	}

	do_progress = save_do_progress;
	if (delete_during == 2)
		do_delayed_deletions(fbuf);
	if (delete_after && !solo_file && file_total > 0)
		do_delete_pass();

	if ((need_retouch_dir_perms || need_retouch_dir_times)
	 && dir_tweaking && (!inc_recurse || delete_during == 2))
		touch_up_dirs(dir_flist, -1);

	if (max_delete >= 0 && deletion_count > max_delete) {
		rprintf(FINFO,
			"Deletions stopped due to --max-delete limit (%d skipped)\n",
			deletion_count - max_delete);
		io_error |= IOERR_DEL_LIMIT;
	}

	if (verbose > 2)
		rprintf(FINFO, "generate_files finished\n");
}