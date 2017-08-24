(!SetEndOfFile(handle)) {
		la_dosmaperr(GetLastError());
		return (-1);
	}