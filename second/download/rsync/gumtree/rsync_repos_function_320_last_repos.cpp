void generate_files(int f_out, const char *local_name)
{
	int i, ndx, next_loopchk = 0;
	char fbuf[MAXPATHLEN];
	int itemizing;
	enum logcode code;
	int save_info_flist = info_levels[INFO_FLIST];
	int save_info_progress = info_levels[INFO_PROGRESS];

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
	need_retouch_dir_times = preserve_times & PRESERVE_DIR_TIMES;
	loopchk_limit = allowed_lull ? allowed_lull * 5 : 200;
	symlink_timeset_failed_flags = ITEM_REPORT_TIME
	    | (protocol_version >= 30 || !am_server ? ITEM_REPORT_TIMEFAIL : 0);
	implied_dirs_are_missing = relative_paths && !implied_dirs && protocol_version < 30;

	if (DEBUG_GTE(GENR, 1))
		rprintf(FINFO, "generator starting pid=%d\n", (int)getpid());

	if (delete_before && !solo_file && cur_flist->used > 0)
		do_delete_pass();
	if (delete_during == 2) {
		deldelay_size = BIGPATHBUFLEN * 4;
		deldelay_buf = new_array(char, deldelay_size);
		if (!deldelay_buf)
			out_of_memory("delete-delay");
	}
	info_levels[INFO_FLIST] = info_levels[INFO_PROGRESS] = 0;

	if (append_mode > 0 || whole_file < 0)
		whole_file = 0;
	if (DEBUG_GTE(FLIST, 1)) {
		rprintf(FINFO, "delta-transmission %s\n",
			whole_file
			? "disabled for local transfer or --whole-file"
			: "enabled");
	}

	dflt_perms = (ACCESSPERMS & ~orig_umask);

	do {
#ifdef SUPPORT_HARD_LINKS
		if (preserve_hard_links && inc_recurse) {
			while (!flist_eof && file_total < MIN_FILECNT_LOOKAHEAD/2)
				wait_for_receiver();
		}
#endif

		if (inc_recurse && cur_flist->parent_ndx >= 0) {
			struct file_struct *fp = dir_flist->files[cur_flist->parent_ndx];
			if (solo_file)
				strlcpy(fbuf, solo_file, sizeof fbuf);
			else
				f_name(fp, fbuf);
			ndx = cur_flist->ndx_start - 1;
			recv_generator(fbuf, fp, ndx, itemizing, code, f_out);
			if (delete_during && dry_run < 2 && !list_only
			 && !(fp->flags & FLAG_MISSING_DIR)) {
				if (fp->flags & FLAG_CONTENT_DIR) {
					dev_t dirdev;
					if (one_file_system) {
						uint32 *devp = F_DIR_DEV_P(fp);
						dirdev = MAKEDEV(DEV_MAJOR(devp), DEV_MINOR(devp));
					} else
						dirdev = MAKEDEV(0, 0);
					delete_in_dir(fbuf, fp, &dirdev);
				} else
					change_local_filter_dir(fbuf, strlen(fbuf), F_DEPTH(fp));
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

			if (i + cur_flist->ndx_start >= next_loopchk) {
				if (allowed_lull)
					maybe_send_keepalive(time(NULL), MSK_ALLOW_FLUSH);
				else
					maybe_flush_socket(0);
				next_loopchk += loopchk_limit;
			}
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
	if (DEBUG_GTE(GENR, 1))
		rprintf(FINFO, "generate_files phase=%d\n", phase);

	while (1) {
		check_for_finished_files(itemizing, code, 1);
		if (msgdone_cnt)
			break;
		wait_for_receiver();
	}

	phase++;
	if (DEBUG_GTE(GENR, 1))
		rprintf(FINFO, "generate_files phase=%d\n", phase);

	write_ndx(f_out, NDX_DONE);

	/* Reduce round-trip lag-time for a useless delay-updates phase. */
	if (protocol_version >= 29 && EARLY_DELAY_DONE_MSG())
		write_ndx(f_out, NDX_DONE);

	if (protocol_version >= 31 && EARLY_DELETE_DONE_MSG()) {
		if ((INFO_GTE(STATS, 2) && (delete_mode || force_delete)) || read_batch)
			write_del_stats(f_out);
		if (EARLY_DELAY_DONE_MSG()) /* Can't send this before delay */
			write_ndx(f_out, NDX_DONE);
	}

	/* Read MSG_DONE for the redo phase (and any prior messages). */
	while (1) {
		check_for_finished_files(itemizing, code, 0);
		if (msgdone_cnt > 1)
			break;
		wait_for_receiver();
	}

	if (protocol_version >= 29) {
		phase++;
		if (DEBUG_GTE(GENR, 1))
			rprintf(FINFO, "generate_files phase=%d\n", phase);
		if (!EARLY_DELAY_DONE_MSG()) {
			write_ndx(f_out, NDX_DONE);
			if (protocol_version >= 31 && EARLY_DELETE_DONE_MSG())
				write_ndx(f_out, NDX_DONE);
		}
		/* Read MSG_DONE for delay-updates phase & prior messages. */
		while (msgdone_cnt == 2)
			wait_for_receiver();
	}

	info_levels[INFO_FLIST] = save_info_flist;
	info_levels[INFO_PROGRESS] = save_info_progress;

	if (delete_during == 2)
		do_delayed_deletions(fbuf);
	if (delete_after && !solo_file && file_total > 0)
		do_delete_pass();

	if (max_delete >= 0 && skipped_deletes) {
		rprintf(FWARNING,
			"Deletions stopped due to --max-delete limit (%d skipped)\n",
			skipped_deletes);
		io_error |= IOERR_DEL_LIMIT;
	}

	if (protocol_version >= 31) {
		if (!EARLY_DELETE_DONE_MSG()) {
			if (INFO_GTE(STATS, 2) || read_batch)
				write_del_stats(f_out);
			write_ndx(f_out, NDX_DONE);
		}

		/* Read MSG_DONE for late-delete phase & prior messages. */
		while (msgdone_cnt == 3)
			wait_for_receiver();
	}

	if ((need_retouch_dir_perms || need_retouch_dir_times)
	 && dir_tweaking && (!inc_recurse || delete_during == 2))
		touch_up_dirs(dir_flist, -1);

	if (DEBUG_GTE(GENR, 1))
		rprintf(FINFO, "generate_files finished\n");
}