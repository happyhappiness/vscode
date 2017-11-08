void exit_cleanup(int code)
{
	io_flush();
	if (cleanup_fname)
		do_unlink(cleanup_fname);
	signal(SIGUSR1, SIG_IGN);
	if (code) {
		kill_all(SIGUSR1);
	}
	exit(code);
}