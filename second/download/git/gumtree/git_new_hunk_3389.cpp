
		munmap(contents, contents_sz);
		contents = NULL;
	}

	if (commit_lock_file(lock) < 0) {
		error_errno("could not write config file %s", config_filename);
		ret = CONFIG_NO_WRITE;
		lock = NULL;
		goto out_free;
	}

	/*
