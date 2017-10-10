	 */
	struct fragment *forward;
	struct fragment *reverse;
	int status;
	int used, used_1;

	forward = parse_binary_hunk(&buffer, &size, &status, &used);
	if (!forward && !status)
		/* there has to be one hunk (forward hunk) */
		return error(_("unrecognized binary patch at line %d"), linenr-1);
	if (status)
		/* otherwise we already gave an error message */
		return status;

	reverse = parse_binary_hunk(&buffer, &size, &status, &used_1);
	if (reverse)
		used += used_1;
	else if (status) {
		/*
		 * Not having reverse hunk is not an error, but having
		 * a corrupt reverse hunk is.
