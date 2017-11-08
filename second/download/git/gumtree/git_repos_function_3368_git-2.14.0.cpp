int refname_is_safe(const char *refname)
{
	const char *rest;

	if (skip_prefix(refname, "refs/", &rest)) {
		char *buf;
		int result;
		size_t restlen = strlen(rest);

		/* rest must not be empty, or start or end with "/" */
		if (!restlen || *rest == '/' || rest[restlen - 1] == '/')
			return 0;

		/*
		 * Does the refname try to escape refs/?
		 * For example: refs/foo/../bar is safe but refs/foo/../../bar
		 * is not.
		 */
		buf = xmallocz(restlen);
		result = !normalize_path_copy(buf, rest) && !strcmp(buf, rest);
		free(buf);
		return result;
	}

	do {
		if (!isupper(*refname) && *refname != '_')
			return 0;
		refname++;
	} while (*refname);
	return 1;
}