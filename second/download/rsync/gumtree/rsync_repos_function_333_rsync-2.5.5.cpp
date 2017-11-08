static RETSIGTYPE sigusr2_handler(int UNUSED(val)) {
	extern int log_got_error;
	if (log_got_error) _exit(RERR_PARTIAL);
	_exit(0);
}