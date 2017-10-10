	int flag;
	int null_is_error = 0;

	if (verbose)
		fprintf(stderr, "Checking HEAD link\n");

	head_points_at = resolve_ref_unsafe("HEAD", 0, head_sha1, &flag);
	if (!head_points_at)
		return error("Invalid HEAD");
	if (!strcmp(head_points_at, "HEAD"))
		/* detached HEAD */
		null_is_error = 1;
	else if (!starts_with(head_points_at, "refs/heads/"))
		return error("HEAD points to something strange (%s)",
			     head_points_at);
	if (is_null_sha1(head_sha1)) {
		if (null_is_error)
			return error("HEAD: detached HEAD points at nothing");
		fprintf(stderr, "notice: HEAD points to an unborn branch (%s)\n",
			head_points_at + 11);
	}
	return 0;
