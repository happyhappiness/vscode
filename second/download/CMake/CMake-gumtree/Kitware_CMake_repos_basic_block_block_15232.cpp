{
			a->fh = CreateFileW(namefull, GENERIC_WRITE, 0, NULL,
			    TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (a->fh == INVALID_HANDLE_VALUE) {
				la_dosmaperr(GetLastError());
				r = errno;
			}
		}