	if (out_fd < 0) {
		ret = error("could not lock config file %s", config_filename);
		goto out;
	}

	if (!(config_file = fopen(config_filename, "rb"))) {
		/* no config file means nothing to rename, no error */
		goto commit_and_out;
	}

	if (fstat(fileno(config_file), &st) == -1) {
		ret = error_errno(_("fstat on %s failed"), config_filename);
