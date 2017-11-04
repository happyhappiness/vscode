void rwrite(enum logcode code, const char *buf, int len, int is_utf8)
{
	int trailing_CR_or_NL;
	FILE *f = msgs2stderr ? stderr : stdout;
#ifdef ICONV_OPTION
	iconv_t ic = is_utf8 && ic_recv != (iconv_t)-1 ? ic_recv : ic_chck;
#else
#ifdef ICONV_CONST
	iconv_t ic = ic_chck;
#endif
#endif

	if (len < 0)
		exit_cleanup(RERR_MESSAGEIO);

	if (msgs2stderr) {
		if (!am_daemon) {
			if (code == FLOG)
				return;
			goto output_msg;
		}
		if (code == FCLIENT)
			return;
		code = FLOG;
	} else if (send_msgs_to_gen) {
		assert(!is_utf8);
		/* Pass the message to our sibling in native charset. */
		send_msg((enum msgcode)code, buf, len, 0);
		return;
	}

	if (code == FERROR_SOCKET) /* This gets simplified for a non-sibling. */
		code = FERROR;
	else if (code == FERROR_UTF8) {
		is_utf8 = 1;
		code = FERROR;
	}

	if (code == FCLIENT)
		code = FINFO;
	else if (am_daemon || logfile_name) {
		static int in_block;
		char msg[2048];
		int priority = code == FINFO || code == FLOG ? LOG_INFO :  LOG_WARNING;

		if (in_block)
			return;
		in_block = 1;
		if (!log_initialised)
			log_init(0);
		strlcpy(msg, buf, MIN((int)sizeof msg, len + 1));
		logit(priority, msg);
		in_block = 0;

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
		f = stderr;
	}

output_msg:
	switch (code) {
	case FERROR_XFER:
		got_xfer_error = 1;
		/* FALL THROUGH */
	case FERROR:
	case FERROR_UTF8:
	case FERROR_SOCKET:
	case FWARNING:
		f = stderr;
		break;
	case FLOG:
	case FINFO:
	case FCLIENT:
		break;
	default:
		fprintf(stderr, "Unknown logcode in rwrite(): %d [%s]\n", (int)code, who_am_i());
		exit_cleanup(RERR_MESSAGEIO);
	}

	if (output_needs_newline) {
		fputc('\n', f);
		output_needs_newline = 0;
	}

	trailing_CR_or_NL = len && (buf[len-1] == '\n' || buf[len-1] == '\r')
			  ? buf[--len] : 0;

	if (len && buf[0] == '\r') {
		fputc('\r', f);
		buf++;
		len--;
	}

#ifdef ICONV_CONST
	if (ic != (iconv_t)-1) {
		xbuf outbuf, inbuf;
		char convbuf[1024];
		int ierrno;

		INIT_CONST_XBUF(outbuf, convbuf);
		INIT_XBUF(inbuf, (char*)buf, len, (size_t)-1);

		while (inbuf.len) {
			iconvbufs(ic, &inbuf, &outbuf, inbuf.pos ? 0 : ICB_INIT);
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