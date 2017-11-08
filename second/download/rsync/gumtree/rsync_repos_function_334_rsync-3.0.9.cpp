NORETURN void out_of_memory(const char *str)
{
	rprintf(FERROR, "ERROR: out of memory in %s [%s]\n", str, who_am_i());
	exit_cleanup(RERR_MALLOC);
}