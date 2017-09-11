 * provide a wrapper.
 */
int
buferror(char *buf, size_t buflen)
{

#ifdef _WIN32
	FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), 0,
	    (LPSTR)buf, buflen, NULL);
	return (0);
#elif defined(_GNU_SOURCE)
	char *b = strerror_r(errno, buf, buflen);
	if (b != buf) {
		strncpy(buf, b, buflen);
		buf[buflen-1] = '\0';
	}
	return (0);
#else
	return (strerror_r(errno, buf, buflen));
#endif
}

uintmax_t
malloc_strtoumax(const char *nptr, char **endptr, int base)
{
	uintmax_t ret, digit;
	int b;
	bool neg;
	const char *p, *ns;

	if (base < 0 || base == 1 || base > 36) {
		set_errno(EINVAL);
		return (UINTMAX_MAX);
	}
	b = base;

	/* Swallow leading whitespace and get sign, if any. */
	neg = false;
	p = nptr;
	while (true) {
		switch (*p) {
		case '\t': case '\n': case '\v': case '\f': case '\r': case ' ':
