static int disable_echo(void)
{
	hconin = CreateFile("CONIN$", GENERIC_READ | GENERIC_WRITE,
	    FILE_SHARE_READ, NULL, OPEN_EXISTING,
	    FILE_ATTRIBUTE_NORMAL, NULL);
	if (hconin == INVALID_HANDLE_VALUE)
		return -1;

	GetConsoleMode(hconin, &cmode);
	sigchain_push_common(restore_term_on_signal);
	if (!SetConsoleMode(hconin, cmode & (~ENABLE_ECHO_INPUT))) {
		CloseHandle(hconin);
		hconin = INVALID_HANDLE_VALUE;
		return -1;
	}

	return 0;
}