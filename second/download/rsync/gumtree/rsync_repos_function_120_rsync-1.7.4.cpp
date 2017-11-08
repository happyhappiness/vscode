int do_open(char *pathname, int flags, mode_t mode)
{
	if (dry_run) return -1;
	return open(pathname, flags, mode);
}