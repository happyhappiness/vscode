{
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