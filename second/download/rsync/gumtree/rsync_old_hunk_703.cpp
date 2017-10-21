	return 0;
}


static void report_exclude_result(char const *name,
                                  struct exclude_struct const *ent,
                                  int name_is_dir)
{
	/* If a trailing slash is present to match only directories,
	 * then it is stripped out by make_exclude.  So as a special
	 * case we add it back in here. */

	if (verbose >= 2)
		rprintf(FINFO, "%s %s %s because of pattern %s%s\n",
			ent->include ? "including" : "excluding",
			name_is_dir ? "directory" : "file",
			name, ent->pattern,
			ent->directory ? "/" : "");
}


/*
 * Return true if file NAME is defined to be excluded by either
 * LOCAL_EXCLUDE_LIST or the globals EXCLUDE_LIST.
 */
int check_exclude(struct exclude_struct **list, char *name, int name_is_dir)
{
	struct exclude_struct *ent;

	while ((ent = *list++) != NULL) {
		if (check_one_exclude(name, ent, name_is_dir)) {
			report_exclude_result(name, ent, name_is_dir);
			return !ent->include;
		}
	}

	return 0;
}


void add_exclude(struct exclude_struct ***listp, const char *pattern, int include)
{
	struct exclude_struct **list = *listp;
	int len = 0;

	if (*pattern == '!' && !pattern[1]) {
	    free_exclude_list(listp);
	    return;
	}

	if (list)
		for (; list[len]; len++) {}

 	list = *listp = realloc_array(list, struct exclude_struct *, len+2);

	if (!list || !(list[len] = make_exclude(pattern, include)))
		out_of_memory("add_exclude");

	if (verbose > 2) {
		rprintf(FINFO,"add_exclude(%s,%s)\n",pattern,
			include ? "include" : "exclude");
	}

	list[len+1] = NULL;
}


void add_exclude_file(struct exclude_struct ***listp, const char *fname,
		      int fatal, int include)
{
	int fd;
	char line[MAXPATHLEN];
	char *eob = line + MAXPATHLEN - 1;
	extern int eol_nulls;

	if (!fname || !*fname)
		return;

	if (*fname != '-' || fname[1])
		fd = open(fname, O_RDONLY|O_BINARY);
	else
		fd = 0;
	if (fd < 0) {
		if (fatal) {
			rsyserr(FERROR, errno,
				"failed to open %s file %s",
				include ? "include" : "exclude",
				fname);
			exit_cleanup(RERR_FILEIO);
		}
		return;
	}

	while (1) {
		char ch, *s = line;
		int cnt;
		while (1) {
			if ((cnt = read(fd, &ch, 1)) <= 0) {
				if (cnt < 0 && errno == EINTR)
					continue;
				break;
			}
			if (eol_nulls? !ch : (ch == '\n' || ch == '\r'))
				break;
			if (s < eob)
				*s++ = ch;
		}
		*s = '\0';
		if (*line && *line != ';' && *line != '#') {
			/* Skip lines starting with semicolon or pound.
			 * It probably wouldn't cause any harm to not skip
			 * them but there's no need to save them. */
			add_exclude(listp, line, include);
		}
		if (cnt <= 0)
			break;
	}
	close(fd);
}


void send_exclude_list(int f)
{
	int i;
	extern int protocol_version;
	extern int list_only, recurse;

	/* This is a complete hack - blame Rusty.
	 *
	 * FIXME: This pattern shows up in the output of
	 * report_exclude_result(), which is not ideal. */
	if (list_only && !recurse)
		add_exclude(&exclude_list, "/*/*", ADD_EXCLUDE);

	if (!exclude_list) {
		write_int(f,0);
		return;
	}

	for (i=0;exclude_list[i];i++) {
		int l;
		char pattern[MAXPATHLEN];

		strlcpy(pattern,exclude_list[i]->pattern,sizeof(pattern));
		if (exclude_list[i]->directory) strlcat(pattern,"/", sizeof(pattern));

		l = strlen(pattern);
		if (l == 0) continue;
		if (exclude_list[i]->include) {
			if (protocol_version < 19) {
				rprintf(FERROR,"remote rsync does not support include syntax - aborting\n");
				exit_cleanup(RERR_UNSUPPORTED);
			}
			write_int(f,l+2);
			write_buf(f,"+ ",2);
		} else {
			write_int(f,l);
		}
		write_buf(f,pattern,l);
	}

	write_int(f,0);
}


void recv_exclude_list(int f)
{
	char line[MAXPATHLEN];
	unsigned int l;

	while ((l=read_int(f))) {
		if (l >= MAXPATHLEN) overflow("recv_exclude_list");
		read_sbuf(f,line,l);
		add_exclude(&exclude_list, line, ADD_EXCLUDE);
	}
}

/* Get the next include/exclude arg from the string. It works in a similar way
** to strtok - initially an arg is sent over, from then on NULL. This
** routine takes into account any +/- in the strings and does not
** consider the space following it as a delimeter.
*/
char *get_exclude_tok(char *p)
{
	static char *s;
	static int more;
	char *t;

	if (p) {
		s=p;
		if (*p)
			more=1;
	}

	if (!more)
		return(NULL);

	/* Skip over any initial spaces */
	while (isspace(* (unsigned char *) s))
		s++;

	/* Are we at the end of the string? */
	if (*s) {
		/* remember the beginning of the token */
		t=s;

		/* Is this a '+' or '-' followed by a space (not whitespace)? */
		if ((*s=='+' || *s=='-') && *(s+1)==' ')
			s+=2;

		/* Skip to the next space or the end of the string */
		while (!isspace(* (unsigned char *) s) && *s != '\0')
			s++;
	} else {
		t=NULL;
	}

	/* Have we reached the end of the string? */
	if (*s)
		*s++='\0';
	else
		more=0;
	return(t);
}


void add_exclude_line(struct exclude_struct ***listp,
		      const char *line, int include)
{
	char *tok, *p;
	if (!line || !*line) return;
	p = strdup(line);
	if (!p) out_of_memory("add_exclude_line");
	for (tok=get_exclude_tok(p); tok; tok=get_exclude_tok(NULL))
		add_exclude(listp, tok, include);
	free(p);
}


static char *cvs_ignore_list[] = {
  "RCS/", "SCCS/", "CVS/", ".svn/", "CVS.adm", "RCSLOG", "cvslog.*",
  "tags", "TAGS", ".make.state", ".nse_depinfo",
  "*~", "#*", ".#*", ", *", "*.old", "*.bak", "*.BAK", "*.orig",
  "*.rej", ".del-*", "*.a", "*.o", "*.obj", "*.so", "*.Z", "*.elc", "*.ln",
  "core", NULL};


void add_cvs_excludes(void)
{
	char fname[MAXPATHLEN];
	char *p;
	int i;

	for (i=0; cvs_ignore_list[i]; i++)
		add_exclude(&exclude_list, cvs_ignore_list[i], ADD_EXCLUDE);

	if ((p=getenv("HOME")) && strlen(p) < (MAXPATHLEN-12)) {
		snprintf(fname,sizeof(fname), "%s/.cvsignore",p);
		add_exclude_file(&exclude_list,fname,MISSING_OK,ADD_EXCLUDE);
	}

	add_exclude_line(&exclude_list, getenv("CVSIGNORE"), ADD_EXCLUDE);
}
