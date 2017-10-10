	if (!ref_count)
		die(_("Refusing to create empty bundle."));
	else if (ref_count < 0)
		return -1;

	/* write pack */
	if (write_pack_data(bundle_fd, &lock, &revs))
		return -1;

	if (!bundle_to_stdout) {
		if (commit_lock_file(&lock))
			die_errno(_("cannot create '%s'"), path);
	}
