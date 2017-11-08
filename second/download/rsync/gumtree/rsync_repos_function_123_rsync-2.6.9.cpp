void write_vstring(int f, char *str, int len)
{
	uchar lenbuf[3], *lb = lenbuf;

	if (len > 0x7F) {
		if (len > 0x7FFF) {
			rprintf(FERROR,
				"attempting to send over-long vstring (%d > %d)\n",
				len, 0x7FFF);
			exit_cleanup(RERR_PROTOCOL);
		}
		*lb++ = len / 0x100 + 0x80;
	}
	*lb = len;

	writefd(f, (char*)lenbuf, lb - lenbuf + 1);
	if (len)
		writefd(f, str, len);
}