	if (argc <= i)
		usage_with_options(verify_tag_usage, verify_tag_options);

	if (verbose)
		flags |= GPG_VERIFY_VERBOSE;

	while (i < argc) {
		unsigned char sha1[20];
		const char *name = argv[i++];
		if (get_sha1(name, sha1))
			had_error = !!error("tag '%s' not found.", name);
		else if (gpg_verify_tag(sha1, name, flags))
			had_error = 1;
	}
	return had_error;
}
