	/* Find common prefix for all pathspec's */
	max_prefix = common_prefix(&pathspec);
	max_prefix_len = max_prefix ? strlen(max_prefix) : 0;

	/* Treat unmatching pathspec elements as errors */
	if (pathspec.nr && error_unmatch)
		ps_matched = xcalloc(pathspec.nr, 1);

	if ((dir.flags & DIR_SHOW_IGNORED) && !exc_given)
		die("ls-files --ignored needs some exclude pattern");

	/* With no flags, we default to showing the cached files */
	if (!(show_stage || show_deleted || show_others || show_unmerged ||
