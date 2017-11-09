static int prune_tmp_file(const char *fullpath)
{
	struct stat st;
	if (lstat(fullpath, &st))
		return error("Could not stat '%s'", fullpath);
	if (st.st_mtime > expire)
		return 0;
	if (show_only || verbose)
		printf("Removing stale temporary file %s\n", fullpath);
	if (!show_only)
		unlink_or_warn(fullpath);
	return 0;
}