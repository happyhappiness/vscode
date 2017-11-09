int send_msg(enum msgcode code, const char *buf, size_t len, int convert)
{
	char *hdr;
	size_t needed, pos;
	BOOL want_debug = DEBUG_GTE(IO, 1) && convert >= 0 && (msgs2stderr || code != MSG_INFO);

	if (!OUT_MULTIPLEXED)
		return 0;

	if (want_debug)
		rprintf(FINFO, "[%s] send_msg(%d, %ld)\n", who_am_i(), (int)code, (long)len);

	/* When checking for enough free space for this message, we need to
	 * make sure that there is space for the 4-byte header, plus we'll
	 * assume that we may waste up to 3 bytes (if the header doesn't fit
	 * at the physical end of the buffer). */
#ifdef ICONV_OPTION
	if (convert > 0 && ic_send == (iconv_t)-1)
		convert = 0;
	if (convert > 0) {
		/* Ensuring double-size room leaves space for maximal conversion expansion. */
		needed = len*2 + 4 + 3;
	} else
#endif
		needed = len + 4 + 3;
	if (iobuf.msg.len + needed > iobuf.msg.size)
		perform_io(needed, PIO_NEED_MSGROOM);

	pos = iobuf.msg.pos + iobuf.msg.len; /* Must be set after any flushing. */
	if (pos >= iobuf.msg.size)
		pos -= iobuf.msg.size;
	else if (pos + 4 > iobuf.msg.size) {
		/* The 4-byte header won't fit at the end of the buffer,
		 * so we'll temporarily reduce the message buffer's size
		 * and put the header at the start of the buffer. */
		reduce_iobuf_size(&iobuf.msg, pos);
		pos = 0;
	}
	hdr = iobuf.msg.buf + pos;

	iobuf.msg.len += 4; /* Allocate room for the coming header bytes. */

#ifdef ICONV_OPTION
	if (convert > 0) {
		xbuf inbuf;

		INIT_XBUF(inbuf, (char*)buf, len, (size_t)-1);

		len = iobuf.msg.len;
		iconvbufs(ic_send, &inbuf, &iobuf.msg,
			  ICB_INCLUDE_BAD | ICB_INCLUDE_INCOMPLETE | ICB_CIRCULAR_OUT | ICB_INIT);
		if (inbuf.len > 0) {
			rprintf(FERROR, "overflowed iobuf.msg buffer in send_msg");
			exit_cleanup(RERR_UNSUPPORTED);
		}
		len = iobuf.msg.len - len;
	} else
#endif
	{
		size_t siz;

		if ((pos += 4) == iobuf.msg.size)
			pos = 0;

		/* Handle a split copy if we wrap around the end of the circular buffer. */
		if (pos >= iobuf.msg.pos && (siz = iobuf.msg.size - pos) < len) {
			memcpy(iobuf.msg.buf + pos, buf, siz);
			memcpy(iobuf.msg.buf, buf + siz, len - siz);
		} else
			memcpy(iobuf.msg.buf + pos, buf, len);

		iobuf.msg.len += len;
	}

	SIVAL(hdr, 0, ((MPLEX_BASE + (int)code)<<24) + len);

	if (want_debug && convert > 0)
		rprintf(FINFO, "[%s] converted msg len=%ld\n", who_am_i(), (long)len);

	return 1;
}