int is_inside_dir(const char *dir)
{
	char *cwd;
	int rc;

	if (!dir)
		return 0;

	cwd = xgetcwd();
	rc = (dir_inside_of(cwd, dir) >= 0);
	free(cwd);
	return rc;
}