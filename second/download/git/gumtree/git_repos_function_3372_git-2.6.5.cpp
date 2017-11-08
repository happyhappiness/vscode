static void transfer_debug(const char *fmt, ...)
{
	va_list args;
	char msgbuf[PBUFFERSIZE];
	static int debug_enabled = -1;

	if (debug_enabled < 0)
		debug_enabled = getenv("GIT_TRANSLOOP_DEBUG") ? 1 : 0;
	if (!debug_enabled)
		return;

	va_start(args, fmt);
	vsnprintf(msgbuf, PBUFFERSIZE, fmt, args);
	va_end(args);
	fprintf(stderr, "Transfer loop debugging: %s\n", msgbuf);
}