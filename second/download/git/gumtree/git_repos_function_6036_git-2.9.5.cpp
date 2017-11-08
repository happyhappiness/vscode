HANDLE winansi_get_osfhandle(int fd)
{
	HANDLE hnd = (HANDLE) _get_osfhandle(fd);
	if (isatty(fd) && GetFileType(hnd) == FILE_TYPE_PIPE) {
		if (fd == 1 && hconsole1)
			return hconsole1;
		else if (fd == 2 && hconsole2)
			return hconsole2;
	}
	return hnd;
}