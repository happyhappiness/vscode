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

	if (progress_is_active && !am_server) {
		fputc('\n', f);
		progress_is_active = 0;
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
