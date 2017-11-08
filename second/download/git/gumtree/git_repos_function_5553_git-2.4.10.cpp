HANDLE winansi_get_osfhandle(int fd)
{
	HANDLE hnd = (HANDLE) _get_osfhandle(fd);
	if ((fd == 1 || fd == 2) && isatty(fd)
	    && GetFileType(hnd) == FILE_TYPE_PIPE)
		return (fd == 1) ? hconsole1 : hconsole2;
	return hnd;
}