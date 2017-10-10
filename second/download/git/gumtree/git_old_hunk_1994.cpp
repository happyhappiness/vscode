}

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

static void imap_warn(const char *msg, ...)
{
	va_list va;

	if (Quiet < 2) {
		va_start(va, msg);
		vfprintf(stderr, msg, va);
		va_end(va);
	}
}

