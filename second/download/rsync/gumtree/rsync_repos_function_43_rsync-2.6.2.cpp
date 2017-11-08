void add_exclude_file(struct exclude_list_struct *listp, const char *fname,
		      int xflags)
{
	FILE *fp;
	char line[MAXPATHLEN];
	char *eob = line + MAXPATHLEN - 1;
	int word_split = xflags & XFLG_WORD_SPLIT;

	if (!fname || !*fname)
		return;

	if (*fname != '-' || fname[1])
		fp = fopen(fname, "rb");
	else
		fp = stdin;
	if (!fp) {
		if (xflags & XFLG_FATAL_ERRORS) {
			rsyserr(FERROR, errno,
				"failed to open %s file %s",
				xflags & XFLG_DEF_INCLUDE ? "include" : "exclude",
				fname);
			exit_cleanup(RERR_FILEIO);
		}
		return;
	}

	while (1) {
		char *s = line;
		int ch;
		while (1) {
			if ((ch = getc(fp)) == EOF) {
				if (ferror(fp) && errno == EINTR)
					continue;
				break;
			}
			if (word_split && isspace(ch))
				break;
			if (eol_nulls? !ch : (ch == '\n' || ch == '\r'))
				break;
			if (s < eob)
				*s++ = ch;
		}
		*s = '\0';
		/* Skip an empty token and (when line parsing) comments. */
		if (*line && (word_split || (*line != ';' && *line != '#')))
			add_exclude(listp, line, xflags);
		if (ch == EOF)
			break;
	}
	fclose(fp);
}