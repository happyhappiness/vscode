void server_options(char **args,int *argc)
{
	static char argstr[64];
	int ac = *argc;
	char *arg;

	int i, x;

	if (blocking_io == -1)
		blocking_io = 0;

	args[ac++] = "--server";

	if (daemon_over_rsh) {
		args[ac++] = "--daemon";
		*argc = ac;
		/* if we're passing --daemon, we're done */
		return;
	}

	if (!am_sender)
		args[ac++] = "--sender";

	x = 1;
	argstr[0] = '-';
	for (i = 0; i < verbose; i++)
		argstr[x++] = 'v';

	/* the -q option is intentionally left out */
	if (make_backups)
		argstr[x++] = 'b';
	if (update_only)
		argstr[x++] = 'u';
	if (!do_xfers) /* NOT "dry_run"! */
		argstr[x++] = 'n';
	if (preserve_links)
		argstr[x++] = 'l';
	if (copy_links)
		argstr[x++] = 'L';
	if (xfer_dirs > 1)
		argstr[x++] = 'd';
	if (keep_dirlinks && am_sender)
		argstr[x++] = 'K';

	if (whole_file > 0)
		argstr[x++] = 'W';
	/* We don't need to send --no-whole-file, because it's the
	 * default for remote transfers, and in any case old versions
	 * of rsync will not understand it. */

	if (preserve_hard_links)
		argstr[x++] = 'H';
	if (preserve_uid)
		argstr[x++] = 'o';
	if (preserve_gid)
		argstr[x++] = 'g';
	if (preserve_devices)
		argstr[x++] = 'D';
	if (preserve_times)
		argstr[x++] = 't';
	if (omit_dir_times == 2 && am_sender)
		argstr[x++] = 'O';
	if (preserve_perms)
		argstr[x++] = 'p';
	if (recurse)
		argstr[x++] = 'r';
	if (always_checksum)
		argstr[x++] = 'c';
	if (cvs_exclude)
		argstr[x++] = 'C';
	if (ignore_times)
		argstr[x++] = 'I';
	if (relative_paths)
		argstr[x++] = 'R';
	if (one_file_system)
		argstr[x++] = 'x';
	if (sparse_files)
		argstr[x++] = 'S';
	if (do_compression)
		argstr[x++] = 'z';

	/* This is a complete hack - blame Rusty.  FIXME!
	 * This hack is only needed for older rsync versions that
	 * don't understand the --list-only option. */
	if (list_only == 1 && !recurse)
		argstr[x++] = 'r';

	argstr[x] = 0;

	if (x != 1)
		args[ac++] = argstr;

	if (list_only > 1)
		args[ac++] = "--list-only";

	/* The server side doesn't use our log-format, but in certain
	 * circumstances they need to know a little about the option. */
	if (log_format && am_sender) {
		if (log_format_has_i)
			args[ac++] = "--log-format=%i";
		else if (log_format_has_o_or_i)
			args[ac++] = "--log-format=%o";
		else if (!verbose)
			args[ac++] = "--log-format=X";
	}

	if (block_size) {
		if (asprintf(&arg, "-B%lu", block_size) < 0)
			goto oom;
		args[ac++] = arg;
	}

	if (max_delete && am_sender) {
		if (asprintf(&arg, "--max-delete=%d", max_delete) < 0)
			goto oom;
		args[ac++] = arg;
	}

	if (max_size && am_sender) {
		args[ac++] = "--max-size";
		args[ac++] = max_size_arg;
	}

	if (io_timeout) {
		if (asprintf(&arg, "--timeout=%d", io_timeout) < 0)
			goto oom;
		args[ac++] = arg;
	}

	if (bwlimit) {
		if (asprintf(&arg, "--bwlimit=%d", bwlimit) < 0)
			goto oom;
		args[ac++] = arg;
	}

	if (backup_dir) {
		args[ac++] = "--backup-dir";
		args[ac++] = backup_dir;
	}

	/* Only send --suffix if it specifies a non-default value. */
	if (strcmp(backup_suffix, backup_dir ? "" : BACKUP_SUFFIX) != 0) {
		/* We use the following syntax to avoid weirdness with '~'. */
		if (asprintf(&arg, "--suffix=%s", backup_suffix) < 0)
			goto oom;
		args[ac++] = arg;
	}

	if (am_sender) {
		if (delete_excluded)
			args[ac++] = "--delete-excluded";
		else if (delete_before == 1 || delete_after)
			args[ac++] = "--delete";
		if (delete_before > 1)
			args[ac++] = "--delete-before";
		if (delete_during)
			args[ac++] = "--delete-during";
		if (delete_after)
			args[ac++] = "--delete-after";
		if (force_delete)
			args[ac++] = "--force";
		if (write_batch < 0)
			args[ac++] = "--only-write-batch=X";
	}

	if (size_only)
		args[ac++] = "--size-only";

	if (modify_window_set) {
		if (asprintf(&arg, "--modify-window=%d", modify_window) < 0)
			goto oom;
		args[ac++] = arg;
	}

	if (checksum_seed) {
		if (asprintf(&arg, "--checksum-seed=%d", checksum_seed) < 0)
			goto oom;
		args[ac++] = arg;
	}

	if (partial_dir && am_sender) {
		if (partial_dir != partialdir_for_delayupdate) {
			args[ac++] = "--partial-dir";
			args[ac++] = partial_dir;
		}
		if (delay_updates)
			args[ac++] = "--delay-updates";
	} else if (keep_partial)
		args[ac++] = "--partial";

	if (ignore_errors)
		args[ac++] = "--ignore-errors";

	if (copy_unsafe_links)
		args[ac++] = "--copy-unsafe-links";

	if (safe_symlinks)
		args[ac++] = "--safe-links";

	if (numeric_ids)
		args[ac++] = "--numeric-ids";

	if (only_existing && am_sender)
		args[ac++] = "--existing";

	if (opt_ignore_existing && am_sender)
		args[ac++] = "--ignore-existing";

	if (inplace)
		args[ac++] = "--inplace";

	if (tmpdir) {
		args[ac++] = "--temp-dir";
		args[ac++] = tmpdir;
	}

	if (basis_dir[0] && am_sender) {
		/* the server only needs this option if it is not the sender,
		 *   and it may be an older version that doesn't know this
		 *   option, so don't send it if client is the sender.
		 */
		int i;
		for (i = 0; i < basis_dir_cnt; i++) {
			args[ac++] = dest_option;
			args[ac++] = basis_dir[i];
		}
	}

	if (files_from && (!am_sender || filesfrom_host)) {
		if (filesfrom_host) {
			args[ac++] = "--files-from";
			args[ac++] = files_from;
			if (eol_nulls)
				args[ac++] = "--from0";
		} else {
			args[ac++] = "--files-from=-";
			args[ac++] = "--from0";
		}
		if (!relative_paths)
			args[ac++] = "--no-relative";
	}
	if (!implied_dirs && !am_sender)
		args[ac++] = "--no-implied-dirs";

	if (fuzzy_basis && am_sender)
		args[ac++] = "--fuzzy";

	if (remove_sent_files)
		args[ac++] = "--remove-sent-files";

	*argc = ac;
	return;

    oom:
	out_of_memory("server_options");
}