struct sha1file *sha1fd_check(const char *name)
{
	int sink, check;
	struct sha1file *f;

	sink = open("/dev/null", O_WRONLY);
	if (sink < 0)
		return NULL;
	check = open(name, O_RDONLY);
	if (check < 0) {
		int saved_errno = errno;
		close(sink);
		errno = saved_errno;
		return NULL;
	}
	f = sha1fd(sink, name);
	f->check_fd = check;
	return f;
}