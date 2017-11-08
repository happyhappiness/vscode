void rsyserr(enum logcode code, int errcode, const char *format, ...)
{
	va_list ap;
	char buf[1024];
	int len;
	size_t sys_len;
	char *sysmsg;

	va_start(ap, format);
	/* Note: might return <0 */
	len = vsnprintf(buf, sizeof(buf), format, ap);
	va_end(ap);

	/* TODO: Put in RSYNC_NAME at the start. */

	if ((size_t) len > sizeof(buf)-1)
		exit_cleanup(RERR_MESSAGEIO);

	sysmsg = strerror(errcode);
	sys_len = strlen(sysmsg);
	if ((size_t) len + 3 + sys_len > sizeof(buf) - 1)
		exit_cleanup(RERR_MESSAGEIO);

	strcpy(buf + len, ": ");
	len += 2;
	strcpy(buf + len, sysmsg);
	len += sys_len;
	strcpy(buf + len, "\n");
	len++;

	rwrite(code, buf, len);
}