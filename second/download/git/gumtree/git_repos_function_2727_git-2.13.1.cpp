static int access_error_is_ok(int err, unsigned flag)
{
	return err == ENOENT || err == ENOTDIR ||
		((flag & ACCESS_EACCES_OK) && err == EACCES);
}