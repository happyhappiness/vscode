{
	HANDLE handle;
	DWORD bytes_read, lasterr;
	int r;

#ifdef _WIN64
	if (nbytes > UINT32_MAX)
		nbytes = UINT32_MAX;
#endif
	if (fd < 0) {
		errno = EBADF;
		return (-1);
	}
	/* Do not pass 0 to third parameter of ReadFile(), read bytes.
	 * This will not return to application side. */
	if (nbytes == 0)
		return (0);
	handle = (HANDLE)_get_osfhandle(fd);
	r = ReadFile(handle, buf, (uint32_t)nbytes,
	    &bytes_read, NULL);
	if (r == 0) {
		lasterr = GetLastError();
		if (lasterr == ERROR_NO_DATA) {
			errno = EAGAIN;
			return (-1);
		}
		if (lasterr == ERROR_BROKEN_PIPE)
			return (0);
		if (lasterr == ERROR_ACCESS_DENIED)
			errno = EBADF;
		else
			la_dosmaperr(lasterr);
		return (-1);
	}
	return ((ssize_t)bytes_read);
}