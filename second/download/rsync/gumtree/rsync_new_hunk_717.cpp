	   more useful */
	if (list_only && !recurse)
		argstr[x++] = 'r';

	argstr[x] = 0;

	if (x != 1)
		args[ac++] = argstr;

	if (block_size) {
		if (asprintf(&arg, "-B%u", block_size) < 0)
			goto oom;
		args[ac++] = arg;
	}

	if (max_delete && am_sender) {
		if (asprintf(&arg, "--max-delete=%d", max_delete) < 0)
			goto oom;
		args[ac++] = arg;
	}

	if (batch_prefix) {
		char *r_or_w = write_batch ? "write" : "read";
		if (asprintf(&arg, "--%s-batch=%s", r_or_w, batch_prefix) < 0)
			goto oom;
		args[ac++] = arg;
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

	if (delete_excluded)
		args[ac++] = "--delete-excluded";
	else if (delete_mode)
		args[ac++] = "--delete";

	if (size_only)
		args[ac++] = "--size-only";

	if (modify_window_set) {
		if (asprintf(&arg, "--modify-window=%d", modify_window) < 0)
			goto oom;
		args[ac++] = arg;
	}

	if (keep_partial)
		args[ac++] = "--partial";

	if (force_delete)
