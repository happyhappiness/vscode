		goto unlock_and_out;
	}

	fstat(fileno(config_file), &st);

	if (chmod(get_lock_file_path(lock), st.st_mode & 07777) < 0) {
		ret = error_errno("chmod on %s failed",
				  get_lock_file_path(lock));
		goto out;
	}

	while (fgets(buf, sizeof(buf), config_file)) {
		int i;
		int length;
