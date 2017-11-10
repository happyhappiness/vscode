static int nfvasprintf(char **strp, const char *fmt, va_list ap)
{
	int len;
	char tmp[8192];

	len = vsnprintf(tmp, sizeof(tmp), fmt, ap);
	if (len < 0)
		die("Fatal: Out of memory");
	if (len >= sizeof(tmp))
		die("imap command overflow!");
	*strp = xmemdupz(tmp, len);
	return len;
}