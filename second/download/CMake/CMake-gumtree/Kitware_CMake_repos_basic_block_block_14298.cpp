{
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