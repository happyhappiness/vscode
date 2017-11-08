void parse_filter_file(struct filter_list_struct *listp, const char *fname,
		       uint32 mflags, int xflags)
{
	FILE *fp;
	char line[BIGPATHBUFLEN];
	char *eob = line + sizeof line - 1;
	int word_split = mflags & MATCHFLG_WORD_SPLIT;

	if (!fname || !*fname)
		return;

	if (*fname != '-' || fname[1] || am_server) {
		if (server_filter_list.head) {
			strlcpy(line, fname, sizeof line);
			clean_fname(line, 1);
			if (check_filter(&server_filter_list, line, 0) < 0)
				fp = NULL;
			else
				fp = fopen(line, "rb");
		} else
			fp = fopen(fname, "rb");
	} else
		fp = stdin;

	if (verbose > 2) {
		rprintf(FINFO, "[%s] parse_filter_file(%s,%x,%x)%s\n",
			who_am_i(), fname, mflags, xflags,
			fp ? "" : " [not found]");
	}

	if (!fp) {
		if (xflags & XFLG_FATAL_ERRORS) {
			rsyserr(FERROR, errno,
				"failed to open %sclude file %s",
				mflags & MATCHFLG_INCLUDE ? "in" : "ex",
				fname);
			exit_cleanup(RERR_FILEIO);
		}
		return;
	}
	dirbuf[dirbuf_len] = '\0';

	while (1) {
		char *s = line;
		int ch, overflow = 0;
		while (1) {
			if ((ch = getc(fp)) == EOF) {
				if (ferror(fp) && errno == EINTR) {
					clearerr(fp);
					continue;
				}
				break;
			}
			if (word_split && isspace(ch))
				break;
			if (eol_nulls? !ch : (ch == '\n' || ch == '\r'))
				break;
			if (s < eob)
				*s++ = ch;
			else
				overflow = 1;
		}
		if (overflow) {
			rprintf(FERROR, "discarding over-long filter: %s...\n", line);
			s = line;
		}
		*s = '\0';
		/* Skip an empty token and (when line parsing) comments. */
		if (*line && (word_split || (*line != ';' && *line != '#')))
			parse_rule(listp, line, mflags, xflags);
		if (ch == EOF)
			break;
	}
	fclose(fp);
}