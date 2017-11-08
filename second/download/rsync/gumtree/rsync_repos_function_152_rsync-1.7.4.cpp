RETSIGTYPE sigusr1_handler(int val) {
	exit_cleanup(1);
}