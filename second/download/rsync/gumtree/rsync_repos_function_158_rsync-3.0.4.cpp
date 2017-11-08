int read_line_old(int f, char *buf, size_t bufsiz)
{
	bufsiz--; /* leave room for the null */
	while (bufsiz > 0) {
		buf[0] = 0;
		read_buf(f, buf, 1);
		if (buf[0] == 0)
			return 0;
		if (buf[0] == '\n')
			break;
		if (buf[0] != '\r') {
			buf++;
			bufsiz--;
		}
	}
	*buf = '\0';
	return bufsiz > 0;
}