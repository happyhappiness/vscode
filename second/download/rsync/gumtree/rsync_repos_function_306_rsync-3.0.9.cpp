void rsyserr(enum logcode code, int errcode, const char *format, ...)
{
	va_list ap;
	char buf[BIGPATHBUFLEN];
	size_t len;

	strlcpy(buf, RSYNC_NAME ": ", sizeof buf);
	len = (sizeof RSYNC_NAME ": ") - 1;

	va_start(ap, format);
	len += vsnprintf(buf + len, sizeof buf - len, format, ap);
	va_end(ap);

	if (len < sizeof buf) {
		len += snprintf(buf + len, sizeof buf - len,
				": %s (%d)\n", strerror(errcode), errcode);
	}
	if (len >= sizeof buf)
		exit_cleanup(RERR_MESSAGEIO);

	rwrite(code, buf, len, 0);
}