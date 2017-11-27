{
	printf ("LOG: %i - %s\n", severity, msg);
	return;
} /* static void my_log (int, const char *) */

/*
 * This function is called before shutting down collectd.
 */
static int my_shutdown (void)
{
	/* close sockets, free data structures, ... */
	return 0;
