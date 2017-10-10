
		munmap(contents, contents_sz);
		contents = NULL;
	}

	if (commit_lock_file(lock) < 0) {
		error("could not write config file %s: %s", config_filename,
		      strerror(errno));
		ret = CONFIG_NO_WRITE;
		lock = NULL;
		goto out_free;
	}

	/*
