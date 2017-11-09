int git_stat(const char *path, struct stat *buf)
{
	int rc = stat(path, buf);
	if (rc == 0)
		buf->st_mode = mode_native_to_git(buf->st_mode);
	return rc;
}