void rprintf(enum logcode code, const char *format, ...)
{
	va_list ap;
	char buf[1024];
	int len;

	va_start(ap, format);
	/* Note: might return -1 */
	len = vsnprintf(buf, sizeof(buf), format, ap);
	va_end(ap);

	/* Deal with buffer overruns.  Instead of panicking, just
	 * truncate the resulting string.  Note that some vsnprintf()s
	 * return -1 on truncation, e.g., glibc 2.0.6 and earlier. */
	if ((size_t) len > sizeof(buf)-1  ||  len < 0) {
		const char ellipsis[] = "[...]";

		/* Reset length, and zero-terminate the end of our buffer */
		len = sizeof(buf)-1;
		buf[len] = '\0';

		/* Copy the ellipsis to the end of the string, but give
		 * us one extra character:
		 *
		 *                  v--- null byte at buf[sizeof(buf)-1]
		 *        abcdefghij0
		 *     -> abcd[...]00  <-- now two null bytes at end
		 *
		 * If the input format string has a trailing newline,
		 * we copy it into that extra null; if it doesn't, well,
		 * all we lose is one byte.  */
		strncpy(buf+len-sizeof(ellipsis), ellipsis, sizeof(ellipsis));
		if (format[strlen(format)-1] == '\n') {
			buf[len-1] = '\n';
		}
	}

	rwrite(code, buf, len);
}