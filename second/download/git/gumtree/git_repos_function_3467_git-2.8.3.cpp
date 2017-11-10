static void imap_warn(const char *msg, ...)
{
	va_list va;

	if (-2 < verbosity) {
		va_start(va, msg);
		vfprintf(stderr, msg, va);
		va_end(va);
	}
}