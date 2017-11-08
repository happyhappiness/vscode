int refname_is_safe(const char *refname)
{
	if (starts_with(refname, "refs/")) {
		char *buf;
		int result;

		buf = xmallocz(strlen(refname));
		/*
		 * Does the refname try to escape refs/?
		 * For example: refs/foo/../bar is safe but refs/foo/../../bar
		 * is not.
		 */
		result = !normalize_path_copy(buf, refname + strlen("refs/"));
		free(buf);
		return result;
	}
	while (*refname) {
		if (!isupper(*refname) && *refname != '_')
			return 0;
		refname++;
	}
	return 1;
}