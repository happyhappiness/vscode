static void imap_info(const char *msg, ...)
{
	va_list va;

	if (!Quiet) {
		va_start(va, msg);
		vprintf(msg, va);
		va_end(va);
		fflush(stdout);
	}
}