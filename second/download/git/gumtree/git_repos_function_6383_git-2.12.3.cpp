HANDLE winansi_get_osfhandle(int fd)
{
	if (fd == 1 && (fd_is_interactive[1] & FD_SWAPPED))
		return hconsole1;
	if (fd == 2 && (fd_is_interactive[2] & FD_SWAPPED))
		return hconsole2;

	return (HANDLE)_get_osfhandle(fd);
}