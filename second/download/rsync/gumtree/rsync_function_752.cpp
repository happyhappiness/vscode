void server_options(char **args,int *argc)
{
	int ac = *argc;
	static char argstr[50];
	static char bsize[30];
	static char iotime[30];
	static char mdelete[30];
	static char mwindow[30];
	static char bw[50];
	/* Leave room for ``--(write|read)-batch='' */
	static char fext[MAXPATHLEN + 15];

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
	for (i=0;i<verbose;i++)
		argstr[x++] = 'v';

	/* the -q option is intentionally left out */
	if (make_backups)
		argstr[x++] = 'b';
	if (update_only)
		argstr[x++] = 'u';
	if (dry_run)
		argstr[x++] = 'n';
	if (preserve_links)
		argstr[x++] = 'l';
	if (copy_links)
		argstr[x++] = 'L';

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

	/* this is a complete hack - blame Rusty

	   this is a hack to make the list_only (remote file list)
	   more useful */
	if (list_only && !recurse)
		argstr[x++] = 'r';

	argstr[x] = 0;

	if (x != 1) args[ac++] = argstr;

	if (block_size) {
		snprintf(bsize,sizeof(bsize),"-B%d",block_size);
		args[ac++] = bsize;
	}

	if (max_delete && am_sender) {
		snprintf(mdelete,sizeof(mdelete),"--max-delete=%d",max_delete);
		args[ac++] = mdelete;
	}

	if (batch_prefix != NULL) {
		char *fmt = "";
		if (write_batch)
			fmt = "--write-batch=%s";
		else
		if (read_batch)
			fmt = "--read-batch=%s";
		snprintf(fext,sizeof(fext),fmt,batch_prefix);
		args[ac++] = fext;
	}

	if (io_timeout) {
		snprintf(iotime,sizeof(iotime),"--timeout=%d",io_timeout);
		args[ac++] = iotime;
	}

	if (bwlimit) {
		snprintf(bw,sizeof(bw),"--bwlimit=%d",bwlimit);
		args[ac++] = bw;
	}

	if (backup_dir) {
		args[ac++] = "--backup-dir";
		args[ac++] = backup_dir;
	}

	/* Only send --suffix if it specifies a non-default value. */
	if (strcmp(backup_suffix, backup_dir? "" : BACKUP_SUFFIX) != 0) {
		char *s = new_array(char, 9+backup_suffix_len+1);
		if (!s)
			out_of_memory("server_options");
		/* We use the following syntax to avoid weirdness with '~'. */
		sprintf(s, "--suffix=%s", backup_suffix);
		args[ac++] = s;
	}

	if (delete_mode && !delete_excluded)
		args[ac++] = "--delete";

	if (delete_excluded)
		args[ac++] = "--delete-excluded";

	if (size_only)
		args[ac++] = "--size-only";

	if (modify_window_set) {
		snprintf(mwindow,sizeof(mwindow),"--modify-window=%d",
			 modify_window);
		args[ac++] = mwindow;
	}

	if (keep_partial)
		args[ac++] = "--partial";

	if (force_delete)
		args[ac++] = "--force";

	if (delete_after)
		args[ac++] = "--delete-after";

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

	if (tmpdir) {
		args[ac++] = "--temp-dir";
		args[ac++] = tmpdir;
	}

	if (compare_dest && am_sender) {
		/* the server only needs this option if it is not the sender,
		 *   and it may be an older version that doesn't know this
		 *   option, so don't send it if client is the sender.
		 */
		args[ac++] = link_dest ? "--link-dest" : "--compare-dest";
		args[ac++] = compare_dest;
	}

	if (files_from && (!am_sender || remote_filesfrom_file)) {
		if (remote_filesfrom_file) {
			args[ac++] = "--files-from";
			args[ac++] = remote_filesfrom_file;
			if (eol_nulls)
				args[ac++] = "--from0";
		} else {
			args[ac++] = "--files-from=-";
			args[ac++] = "--from0";
		}
	}

	*argc = ac;
}