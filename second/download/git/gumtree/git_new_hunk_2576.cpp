	int ref_count = 0;
	struct rev_info revs;

	bundle_to_stdout = !strcmp(path, "-");
	if (bundle_to_stdout)
		bundle_fd = 1;
	else {
		bundle_fd = hold_lock_file_for_update(&lock, path,
						      LOCK_DIE_ON_ERROR);

		/*
		 * write_pack_data() will close the fd passed to it,
		 * but commit_lock_file() will also try to close the
		 * lockfile's fd. So make a copy of the file
		 * descriptor to avoid trying to close it twice.
		 */
		bundle_fd = dup(bundle_fd);
		if (bundle_fd < 0)
			die_errno("unable to dup file descriptor");
	}

	/* write signature */
	write_or_die(bundle_fd, bundle_signature, strlen(bundle_signature));

	/* init revs to list objects for pack-objects later */
	save_commit_buffer = 0;
	init_revisions(&revs, NULL);
