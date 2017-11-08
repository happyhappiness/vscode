static RETSIGTYPE sigusr1_handler(int UNUSED(val)) {
	exit_cleanup(RERR_SIGNAL);
}