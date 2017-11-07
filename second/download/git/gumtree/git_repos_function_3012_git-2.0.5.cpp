static int nfsnprintf(char *buf, int blen, const char *fmt, ...)
{
	int ret;
	va_list va;

	va_start(va, fmt);
	if (blen <= 0 || (unsigned)(ret = vsnprintf(buf, blen, fmt, va)) >= (unsigned)blen)
		die("Fatal: buffer too small. Please report a bug.");
	va_end(va);
	return ret;
}