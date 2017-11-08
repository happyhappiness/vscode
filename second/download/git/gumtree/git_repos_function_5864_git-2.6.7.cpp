static HANDLE swap_osfhnd(int fd, HANDLE new_handle)
{
	ioinfo *pioinfo;
	HANDLE old_handle;

	/* init ioinfo size if we haven't done so */
	if (init_sizeof_ioinfo())
		return INVALID_HANDLE_VALUE;

	/* get ioinfo pointer and change the handles */
	pioinfo = _pioinfo(fd);
	old_handle = pioinfo->osfhnd;
	pioinfo->osfhnd = new_handle;
	return old_handle;
}