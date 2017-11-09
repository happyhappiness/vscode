static int access_error_is_ok(int err, unsigned flag)
{
	return (is_missing_file_error(err) ||
		((flag & ACCESS_EACCES_OK) && err == EACCES));
}