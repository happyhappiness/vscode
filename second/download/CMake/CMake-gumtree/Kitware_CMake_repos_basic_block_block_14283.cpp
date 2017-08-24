{
#if defined(__BORLANDC__)
		/* Borland has no mode argument.
		   TODO: Fix mode of new file.  */
		r = _open(path, flags);
#else
		r = _open(path, flags, pmode);
#endif
		if (r < 0 && errno == EACCES && (flags & O_CREAT) != 0) {
			/* Simulate other POSIX system action to pass our test suite. */
			attr = GetFileAttributesA(path);
			if (attr == (DWORD)-1)
				la_dosmaperr(GetLastError());
			else if (attr & FILE_ATTRIBUTE_DIRECTORY)
				errno = EISDIR;
			else
				errno = EACCES;
			return (-1);
		}
		if (r >= 0 || errno != ENOENT)
			return (r);
		ws = __la_win_permissive_name(path);
		if (ws == NULL) {
			errno = EINVAL;
			return (-1);
		}
	}