void parse_filter_file(filter_rule_list *listp, const char *fname, const filter_rule *template, int xflags)
{
	FILE *fp;
	char line[BIGPATHBUFLEN];
	char *eob = line + sizeof line - 1;
	BOOL word_split = (template->rflags & FILTRULE_WORD_SPLIT) != 0;

	if (!fname || !*fname)
		return;

	if (*fname != '-' || fname[1] || am_server) {
		if (daemon_filter_list.head) {
			strlcpy(line, fname, sizeof line);
			clean_fname(line, CFN_COLLAPSE_DOT_DOT_DIRS);
			if (check_filter(&daemon_filter_list, FLOG, line, 0) < 0)
				fp = NULL;
			else
				fp = fopen(line, "rb");
		} else
			fp = fopen(fname, "rb");
	} else
		fp = stdin;

	if (DEBUG_GTE(FILTER, 2)) {
		rprintf(FINFO, "[%s] parse_filter_file(%s,%x,%x)%s\n",
			who_am_i(), fname, template->rflags, xflags,
			fp ? "" : " [not found]");
	}

	if (!fp) {
		if (xflags & XFLG_FATAL_ERRORS) {
			rsyserr(FERROR, errno,
				"failed to open %sclude file %s",
				template->rflags & FILTRULE_INCLUDE ? "in" : "ex",
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
			parse_filter_str(listp, line, template, xflags);
		if (ch == EOF)
			break;
	}
	fclose(fp);
}