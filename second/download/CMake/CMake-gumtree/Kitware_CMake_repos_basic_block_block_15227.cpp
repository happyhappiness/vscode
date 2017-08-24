(GetLastError() == ERROR_ACCESS_DENIED) {
				DWORD attr;
				/* Simulate an errno of POSIX system. */
				attr = GetFileAttributesW(fullname);
				if (attr == (DWORD)-1)
					la_dosmaperr(GetLastError());
				else if (attr & FILE_ATTRIBUTE_DIRECTORY)
					errno = EISDIR;
				else
					errno = EACCES;
			} else
				la_dosmaperr(GetLastError())