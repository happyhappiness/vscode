static void check_good_are_ancestors_of_bad(const char *prefix, int no_checkout)
{
	char *filename = git_pathdup("BISECT_ANCESTORS_OK");
	struct stat st;
	int fd;

	if (!current_bad_sha1)
		die("a bad revision is needed");

	/* Check if file BISECT_ANCESTORS_OK exists. */
	if (!stat(filename, &st) && S_ISREG(st.st_mode))
		goto done;

