static void mplex_write(int fd, enum msgcode code, const char *buf, size_t len, int convert)
{
	char buffer[BIGPATHBUFLEN]; /* Oversized for use by iconv code. */
	size_t n = len;

#ifdef ICONV_OPTION
	/* We need to convert buf before doing anything else so that we
	 * can include the (converted) byte length in the message header. */
	if (convert && ic_send != (iconv_t)-1) {
		xbuf outbuf, inbuf;

		INIT_XBUF(outbuf, buffer + 4, 0, sizeof buffer - 4);
		INIT_XBUF(inbuf, (char*)buf, len, -1);

		iconvbufs(ic_send, &inbuf, &outbuf,
			  ICB_INCLUDE_BAD | ICB_INCLUDE_INCOMPLETE);
		if (inbuf.len > 0) {
			rprintf(FERROR, "overflowed conversion buffer in mplex_write");
			exit_cleanup(RERR_UNSUPPORTED);
		}

		n = len = outbuf.len;
	} else
#endif
	if (n > 1024 - 4) /* BIGPATHBUFLEN can handle 1024 bytes */
		n = 0;    /* We'd rather do 2 writes than too much memcpy(). */
	else
		memcpy(buffer + 4, buf, n);

	SIVAL(buffer, 0, ((MPLEX_BASE + (int)code)<<24) + len);

	keep_defer_forwarding++; /* defer_forwarding_messages++ on return */
	writefd_unbuffered(fd, buffer, n+4);
	keep_defer_forwarding--;

	if (len > n)
		writefd_unbuffered(fd, buf+n, len-n);

	if (!--defer_forwarding_messages && !no_flush)
		msg_flush();
}