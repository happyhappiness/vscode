int do_open(char *pathname, int flags, mode_t mode)
{
	if (flags != O_RDONLY) {
	    if (dry_run) return -1;
	    CHECK_RO
	}
	/* some systems can't handle a double / */
	if (pathname[0] == '/' && pathname[1] == '/') pathname++;

	return open(pathname, flags | O_BINARY, mode);
}