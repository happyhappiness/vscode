static NORETURN void fatal_unsafe_io_error(void)
{
	/* This (sadly) can only happen when pushing data because
	 * the sender does not know about what kind of delete
	 * is in effect on the receiving side when pulling. */
	rprintf(FERROR_XFER, "FATAL I/O ERROR: dying to avoid a --delete-during issue with a pre-3.0.7 receiver.\n");
	exit_cleanup(RERR_UNSUPPORTED);
}