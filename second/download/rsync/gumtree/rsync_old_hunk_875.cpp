
	writefd(f, (char*)lenbuf, lb - lenbuf + 1);
	if (len)
		writefd(f, str, len);
}

/**
 * Read a line of up to @p maxlen characters into @p buf (not counting
 * the trailing null).  Strips the (required) trailing newline and all
 * carriage returns.
 *
 * @return 1 for success; 0 for I/O error or truncation.
 **/
int read_line(int f, char *buf, size_t maxlen)
{
	while (maxlen) {
		buf[0] = 0;
		read_buf(f, buf, 1);
		if (buf[0] == 0)
			return 0;
		if (buf[0] == '\n')
			break;
		if (buf[0] != '\r') {
			buf++;
			maxlen--;
		}
	}
	*buf = '\0';
	return maxlen > 0;
}

void io_printf(int fd, const char *format, ...)
{
	va_list ap;
	char buf[BIGPATHBUFLEN];
