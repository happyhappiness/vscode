void setup_iconv(void)
{
	const char *defset = default_charset();
# ifdef ICONV_OPTION
	const char *charset;
	char *cp;
# endif

	if (!am_server && !allow_8bit_chars) {
		/* It's OK if this fails... */
		ic_chck = iconv_open(defset, defset);

		if (verbose > 3) {
			if (ic_chck == (iconv_t)-1) {
				rprintf(FINFO,
					"note: iconv_open(\"%s\", \"%s\") failed (%d)"
					" -- using isprint() instead of iconv().\n",
					defset, defset, errno);
			} else {
				rprintf(FINFO,
					"note: iconv_open(\"%s\", \"%s\") succeeded.\n",
					defset, defset);
			}
		}
	}

# ifdef ICONV_OPTION
	if (!iconv_opt)
		return;

	if ((cp = strchr(iconv_opt, ',')) != NULL) {
		if (am_server) /* A local transfer needs this. */
			iconv_opt = cp + 1;
		else
			*cp = '\0';
	}

	if (!*iconv_opt || (*iconv_opt == '.' && iconv_opt[1] == '\0'))
		charset = defset;
	else
		charset = iconv_opt;

	if ((ic_send = iconv_open(UTF8_CHARSET, charset)) == (iconv_t)-1) {
		rprintf(FERROR, "iconv_open(\"%s\", \"%s\") failed\n",
			UTF8_CHARSET, charset);
		exit_cleanup(RERR_UNSUPPORTED);
	}

	if ((ic_recv = iconv_open(charset, UTF8_CHARSET)) == (iconv_t)-1) {
		rprintf(FERROR, "iconv_open(\"%s\", \"%s\") failed\n",
			charset, UTF8_CHARSET);
		exit_cleanup(RERR_UNSUPPORTED);
	}

	if (verbose > 1) {
		rprintf(FINFO, "%s charset: %s\n",
			am_server ? "server" : "client",
			*charset ? charset : "[LOCALE]");
	}
# endif
}