int git_lstat(const char *path, struct stat *buf)
{
	int rc = lstat(path, buf);
	if (rc == 0)
		buf->st_mode = mode_native_to_git(buf->st_mode);
	return rc;
}