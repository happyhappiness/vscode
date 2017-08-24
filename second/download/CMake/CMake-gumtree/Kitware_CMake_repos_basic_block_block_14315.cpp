{
	DWORD cs;

	(void)option;/* UNUSED */
	do {
		if (GetExitCodeProcess(child, &cs) == 0) {
			CloseHandle(child);
			la_dosmaperr(GetLastError());
			*status = 0;
			return (-1);
		}
	} while (cs == STILL_ACTIVE);

	*status = (int)(cs & 0xff);
	return (0);
}