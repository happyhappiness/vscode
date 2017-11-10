void winansi_init(void)
{
	int con1, con2;
	char name[32];

	/* check if either stdout or stderr is a console output screen buffer */
	con1 = is_console(1);
	con2 = is_console(2);

	/* Also compute console bit for fd 0 even though we don't need the result here. */
	is_console(0);

	if (!con1 && !con2) {
#ifdef DETECT_MSYS_TTY
		/* check if stdin / stdout / stderr are MSYS2 pty pipes */
		detect_msys_tty(0);
		detect_msys_tty(1);
		detect_msys_tty(2);
#endif
		return;
	}

	/* create a named pipe to communicate with the console thread */
	xsnprintf(name, sizeof(name), "\\\\.\\pipe\\winansi%lu", GetCurrentProcessId());
	hwrite = CreateNamedPipe(name, PIPE_ACCESS_OUTBOUND,
		PIPE_TYPE_BYTE | PIPE_WAIT, 1, BUFFER_SIZE, 0, 0, NULL);
	if (hwrite == INVALID_HANDLE_VALUE)
		die_lasterr("CreateNamedPipe failed");

	hread = CreateFile(name, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hread == INVALID_HANDLE_VALUE)
		die_lasterr("CreateFile for named pipe failed");

	/* start console spool thread on the pipe's read end */
	hthread = CreateThread(NULL, 0, console_thread, NULL, 0, NULL);
	if (hthread == INVALID_HANDLE_VALUE)
		die_lasterr("CreateThread(console_thread) failed");

	/* schedule cleanup routine */
	if (atexit(winansi_exit))
		die_errno("atexit(winansi_exit) failed");

	/* redirect stdout / stderr to the pipe */
	if (con1)
		hconsole1 = swap_osfhnd(1, duplicate_handle(hwrite));
	if (con2)
		hconsole2 = swap_osfhnd(2, duplicate_handle(hwrite));
}