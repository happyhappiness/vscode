static void filtered_fwrite(FILE *f, const char *buf, int len, int use_isprint)
{
	const char *s, *end = buf + len;
	for (s = buf; s < end; s++) {
		if ((s < end - 4
		  && *s == '\\' && s[1] == '#'
		  && isDigit(s + 2)
		  && isDigit(s + 3)
		  && isDigit(s + 4))
		 || (*s != '\t'
		  && ((use_isprint && !isPrint(s))
		   || *(uchar*)s < ' '))) {
			if (s != buf && fwrite(buf, s - buf, 1, f) != 1)
				exit_cleanup(RERR_MESSAGEIO);
			fprintf(f, "\\#%03o", *(uchar*)s);
			buf = s + 1;
		}
	}
	if (buf != end && fwrite(buf, end - buf, 1, f) != 1)
		exit_cleanup(RERR_MESSAGEIO);
}

/* this is the underlying (unformatted) rsync debugging function. Call
 * it with FINFO, FERROR_*, FWARNING, FLOG, or FCLIENT.  Note: recursion
 * can happen with certain fatal conditions. */
void rwrite(enum logcode code, const char *buf, int len, int is_utf8)
{
	int trailing_CR_or_NL;
	FILE *f = NULL;
#ifdef ICONV_OPTION
	iconv_t ic = is_utf8 && ic_recv != (iconv_t)-1 ? ic_recv : ic_chck;
#else
#ifdef ICONV_CONST
	iconv_t ic = ic_chck;
#endif
#endif

	if (len < 0)
		exit_cleanup(RERR_MESSAGEIO);

	if (am_server && msg_fd_out >= 0) {
		assert(!is_utf8);
		/* Pass the message to our sibling. */
		send_msg((enum msgcode)code, buf, len, 0);
		return;
	}

	if (code == FERROR_SOCKET) /* This gets simplified for a non-sibling. */
		code = FERROR;

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
