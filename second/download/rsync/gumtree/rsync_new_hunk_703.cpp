	return 0;
}


static void report_exclude_result(char const *name,
                                  struct exclude_struct const *ent,
                                  int name_is_dir, const char *type)
{
	/* If a trailing slash is present to match only directories,
	 * then it is stripped out by make_exclude.  So as a special
	 * case we add it back in here. */

	if (verbose >= 2) {
		rprintf(FINFO, "[%s] %scluding %s %s because of %spattern %s%s\n",
			who_am_i(), ent->include ? "in" : "ex",
			name_is_dir ? "directory" : "file", name, type,
			ent->pattern, ent->directory ? "/" : "");
	}
}


/*
 * Return -1 if file "name" is defined to be excluded by the specified
 * exclude list, 1 if it is included, and 0 if it was not matched.
 */
int check_exclude(struct exclude_list_struct *listp, char *name, int name_is_dir)
{
	struct exclude_struct *ent;

	for (ent = listp->head; ent; ent = ent->next) {
		if (check_one_exclude(name, ent, name_is_dir)) {
			report_exclude_result(name, ent, name_is_dir,
					      listp->debug_type);
			return ent->include ? 1 : -1;
		}
	}

	return 0;
}


/* Get the next include/exclude arg from the string.  The token will not
 * be '\0' terminated, so use the returned length to limit the string.
 * Also, be sure to add this length to the returned pointer before passing
 * it back to ask for the next token.  This routine will not parse the +/-
 * prefixes or the "!" token when xflags contains XFLG_WORDS_ONLY.  The
 * *incl_ptr value will be 1 for an include, 0 for an exclude, and -1 for
 * the list-clearing "!" token.
 */
static const char *get_exclude_tok(const char *p, int *len_ptr, int *incl_ptr,
				   int xflags)
{
	const unsigned char *s = (const unsigned char *)p;
	int len;

	if (xflags & XFLG_WORD_SPLIT) {
		/* Skip over any initial whitespace. */
		while (isspace(*s))
			s++;
		/* Update for "!" check. */
		p = (const char *)s;
	}

	/* Is this a '+' or '-' followed by a space (not whitespace)? */
	if (!(xflags & XFLG_WORDS_ONLY)
	    && (*s == '-' || *s == '+') && s[1] == ' ') {
		*incl_ptr = *s == '+';
		s += 2;
	} else
		*incl_ptr = xflags & XFLG_DEF_INCLUDE;

	if (xflags & XFLG_WORD_SPLIT) {
		const unsigned char *cp = s;
		/* Token ends at whitespace or the end of the string. */
		while (!isspace(*cp) && *cp != '\0')
			cp++;
		len = cp - s;
	} else
		len = strlen(s);

	if (*p == '!' && len == 1 && !(xflags & XFLG_WORDS_ONLY))
		*incl_ptr = -1;

	*len_ptr = len;
	return (const char *)s;
}


void add_exclude(struct exclude_list_struct *listp, const char *pattern,
		 int xflags)
{
	int pat_len, incl;
	const char *cp;

	if (!pattern)
		return;

	cp = pattern;
	pat_len = 0;
	while (1) {
		cp = get_exclude_tok(cp + pat_len, &pat_len, &incl, xflags);
		if (!pat_len)
			break;
		/* If we got the special "!" token, clear the list. */
		if (incl < 0)
			free_exclude_list(listp);
		else {
			make_exclude(listp, cp, pat_len, incl);

			if (verbose > 2) {
				rprintf(FINFO, "[%s] add_exclude(%.*s, %s%s)\n",
					who_am_i(), pat_len, cp,
					listp->debug_type,
					incl ? "include" : "exclude");
			}
		}
	}
}


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


void send_exclude_list(int f)
{
	struct exclude_struct *ent;

	/* This is a complete hack - blame Rusty.
	 *
	 * FIXME: This pattern shows up in the output of
	 * report_exclude_result(), which is not ideal. */
	if (list_only && !recurse)
		add_exclude(&exclude_list, "/*/*", 0);

	for (ent = exclude_list.head; ent; ent = ent->next) {
		unsigned int l;
		char p[MAXPATHLEN+1];

		l = strlcpy(p, ent->pattern, sizeof p);
		if (l == 0 || l >= MAXPATHLEN)
			continue;
		if (ent->directory) {
			p[l++] = '/';
			p[l] = '\0';
		}

		if (ent->include) {
			write_int(f, l + 2);
			write_buf(f, "+ ", 2);
		} else if ((*p == '-' || *p == '+') && p[1] == ' ') {
			write_int(f, l + 2);
			write_buf(f, "- ", 2);
		} else
			write_int(f, l);
		write_buf(f, p, l);
	}

	write_int(f, 0);
}


void recv_exclude_list(int f)
{
	char line[MAXPATHLEN+1]; /* Allows a trailing slash on a max-len dir */
	unsigned int l;

	while ((l = read_int(f)) != 0) {
		if (l >= sizeof line)
			overflow("recv_exclude_list");
		read_sbuf(f, line, l);
		add_exclude(&exclude_list, line, 0);
	}
}


static char default_cvsignore[] = 
	/* These default ignored items come from the CVS manual. */
	"RCS SCCS CVS CVS.adm RCSLOG cvslog.* tags TAGS"
	" .make.state .nse_depinfo *~ #* .#* ,* _$* *$"
	" *.old *.bak *.BAK *.orig *.rej .del-*"
	" *.a *.olb *.o *.obj *.so *.exe"
	" *.Z *.elc *.ln core"
	/* The rest we added to suit ourself. */
	" .svn/";

void add_cvs_excludes(void)
{
	char fname[MAXPATHLEN];
	char *p;

	add_exclude(&exclude_list, default_cvsignore,
		    XFLG_WORD_SPLIT | XFLG_WORDS_ONLY);

	if ((p = getenv("HOME"))
	    && pathjoin(fname, sizeof fname, p, ".cvsignore") < sizeof fname) {
		add_exclude_file(&exclude_list, fname,
				 XFLG_WORD_SPLIT | XFLG_WORDS_ONLY);
	}

	add_exclude(&exclude_list, getenv("CVSIGNORE"),
		    XFLG_WORD_SPLIT | XFLG_WORDS_ONLY);
}
