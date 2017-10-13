static void xdl_bug(const char *msg)
{
	fprintf(stderr, "BUG: %s\n", msg);
	exit(1);
}