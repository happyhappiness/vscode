		usage_with_options(merge_file_usage, options);
	if (quiet) {
		if (!freopen("/dev/null", "w", stderr))
			return error_errno("failed to redirect stderr to /dev/null");
	}

	if (prefix)
		prefixlen = strlen(prefix);

	for (i = 0; i < 3; i++) {
		const char *fname = prefix_filename(prefix, prefixlen, argv[i]);
		if (!names[i])
			names[i] = argv[i];
		if (read_mmfile(mmfs + i, fname))
			return -1;
		if (mmfs[i].size > MAX_XDIFF_SIZE ||
		    buffer_is_binary(mmfs[i].ptr, mmfs[i].size))
			return error("Cannot merge binary files: %s",
					argv[i]);
	}

