int git_fstat(int fd, struct stat *buf)
{
	int rc = fstat(fd, buf);
	if (rc == 0)
		buf->st_mode = mode_native_to_git(buf->st_mode);
	return rc;
}