void overflow_exit(char *str)
{
	rprintf(FERROR, "ERROR: buffer overflow in %s\n", str);
	exit_cleanup(RERR_MALLOC);
}