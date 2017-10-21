		if (am_daemon) {
			/* TODO: can we send the error to the user somehow? */
			return;
		}
	}

	switch (code) {
	case FERROR:
		log_got_error = 1;
		f = stderr;
		goto pre_scan;
	case FINFO:
		f = am_server ? stderr : stdout;
	pre_scan:
		while (len > 1 && *buf == '\n') {
			fputc(*buf, f);
			buf++;
			len--;
		}
		break;
	case FNAME:
		f = am_server ? stderr : stdout;
		break;
	default:
		exit_cleanup(RERR_MESSAGEIO);
	}

	trailing_CR_or_NL = len && (buf[len-1] == '\n' || buf[len-1] == '\r')
			  ? buf[--len] : 0;

#if defined HAVE_ICONV_OPEN && defined HAVE_ICONV_H
	if (ic_chck != (iconv_t)-1) {
		char convbuf[1024];
		char *in_buf = buf, *out_buf = convbuf;
		size_t in_cnt = len, out_cnt = sizeof convbuf - 1;

		iconv(ic_chck, NULL, 0, NULL, 0);
		while (iconv(ic_chck, &in_buf,&in_cnt,
				 &out_buf,&out_cnt) == (size_t)-1) {
			if (out_buf != convbuf) {
				filtered_fwrite(f, convbuf, out_buf - convbuf, 0);
				out_buf = convbuf;
				out_cnt = sizeof convbuf - 1;
			}
			if (errno == E2BIG)
				continue;
			fprintf(f, "\\#%03o", *(uchar*)in_buf++);
			in_cnt--;
		}
		if (out_buf != convbuf)
			filtered_fwrite(f, convbuf, out_buf - convbuf, 0);
	} else
#endif
		filtered_fwrite(f, buf, len, !allow_8bit_chars);

	if (trailing_CR_or_NL) {
		fputc(trailing_CR_or_NL, f);
		fflush(f);
	}
}

/* This is the rsync debugging function. Call it with FINFO, FERROR or
 * FLOG. */
void rprintf(enum logcode code, const char *format, ...)
{
	va_list ap;
	char buf[BIGPATHBUFLEN];
	size_t len;

	va_start(ap, format);
	len = vsnprintf(buf, sizeof buf, format, ap);
	va_end(ap);

	/* Deal with buffer overruns.  Instead of panicking, just
	 * truncate the resulting string.  (Note that configure ensures
	 * that we have a vsnprintf() that doesn't ever return -1.) */
	if (len > sizeof buf - 1) {
		static const char ellipsis[] = "[...]";

		/* Reset length, and zero-terminate the end of our buffer */
		len = sizeof buf - 1;
		buf[len] = '\0';

		/* Copy the ellipsis to the end of the string, but give
