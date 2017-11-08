NORETURN void overflow_exit(char *str)
{
	rprintf(FERROR, "ERROR: buffer overflow in %s [%s]\n", str, who_am_i());
	exit_cleanup(RERR_MALLOC);
}