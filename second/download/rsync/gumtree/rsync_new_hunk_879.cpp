
		if (code == FLOG || (am_daemon && !am_server))
			return;
	} else if (code == FLOG)
		return;

	if (quiet && code == FINFO)
		return;

	if (am_server) {
		enum msgcode msg = (enum msgcode)code;
		if (protocol_version < 30) {
			if (msg == MSG_ERROR)
				msg = MSG_ERROR_XFER;
			else if (msg == MSG_WARNING)
				msg = MSG_INFO;
		}
		/* Pass the message to the non-server side. */
		if (send_msg(msg, buf, len, !is_utf8))
			return;
		if (am_daemon) {
			/* TODO: can we send the error to the user somehow? */
			return;
		}
	}

	switch (code) {
	case FERROR_XFER:
		got_xfer_error = 1;
		/* FALL THROUGH */
	case FERROR:
	case FWARNING:
		f = stderr;
		break;
	case FINFO:
		f = am_server ? stderr : stdout;
		break;
	default:
		exit_cleanup(RERR_MESSAGEIO);
	}

	trailing_CR_or_NL = len && (buf[len-1] == '\n' || buf[len-1] == '\r')
			  ? buf[--len] : 0;

#ifdef ICONV_CONST
	if (ic != (iconv_t)-1) {
		xbuf outbuf, inbuf;
		char convbuf[1024];
		int ierrno;

		INIT_CONST_XBUF(outbuf, convbuf);
		INIT_XBUF(inbuf, (char*)buf, len, -1);

		while (inbuf.len) {
			iconvbufs(ic, &inbuf, &outbuf, 0);
			ierrno = errno;
			if (outbuf.len) {
				filtered_fwrite(f, convbuf, outbuf.len, 0);
				outbuf.len = 0;
			}
			if (!ierrno || ierrno == E2BIG)
				continue;
			fprintf(f, "\\#%03o", CVAL(inbuf.buf, inbuf.pos++));
			inbuf.len--;
		}
	} else
#endif
		filtered_fwrite(f, buf, len, !allow_8bit_chars);

	if (trailing_CR_or_NL) {
		fputc(trailing_CR_or_NL, f);
		fflush(f);
	}
}

/* This is the rsync debugging function. Call it with FINFO, FERROR_*,
 * FWARNING, FLOG, or FCLIENT. */
void rprintf(enum logcode code, const char *format, ...)
{
	va_list ap;
	char buf[BIGPATHBUFLEN];
	size_t len;

