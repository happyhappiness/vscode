static void check_good_are_ancestors_of_bad(const char *prefix, int no_checkout)
{
	char *filename = git_pathdup("BISECT_ANCESTORS_OK");
	struct stat st;
	int fd;

	if (!current_bad_oid)
		die("a bad revision is needed");

	/* Check if file BISECT_ANCESTORS_OK exists. */
	if (!stat(filename, &st) && S_ISREG(st.st_mode))
		goto done;

	/* Bisecting with no good rev is ok. */
	if (good_revs.nr == 0)
		goto done;

	/* Check if all good revs are ancestor of the bad rev. */
	if (check_ancestors(prefix))
		check_merge_bases(no_checkout);

	/* Create file BISECT_ANCESTORS_OK. */
	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (fd < 0)
		warning("could not create file '%s': %s",
			filename, strerror(errno));
	else
		close(fd);
 done:
	free(filename);
}