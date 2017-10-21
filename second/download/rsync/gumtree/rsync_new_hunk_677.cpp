		ret->include = 1;
		pattern += 2;
	} else {
		ret->include = include;
	}

	if (exclude_path_prefix)
		ret->match_flags |= MATCHFLG_ABS_PATH;
	if (exclude_path_prefix && *pattern == '/') {
		ret->pattern = new_array(char,
			strlen(exclude_path_prefix) + strlen(pattern) + 1);
		if (!ret->pattern) out_of_memory("make_exclude");
		sprintf(ret->pattern, "%s%s", exclude_path_prefix, pattern);
	}
	else {
		ret->pattern = strdup(pattern);
		if (!ret->pattern) out_of_memory("make_exclude");
	}

	if (strpbrk(pattern, "*[?")) {
		ret->match_flags |= MATCHFLG_WILD;
		if (strstr(pattern, "**")) {
			ret->match_flags |= MATCHFLG_WILD2;
			/* If the pattern starts with **, note that. */
			if (*pattern == '*' && pattern[1] == '*')
				ret->match_flags |= MATCHFLG_WILD2_PREFIX;
		}
	}

	pat_len = strlen(ret->pattern);
	if (pat_len > 1 && ret->pattern[pat_len-1] == '/') {
		ret->pattern[pat_len-1] = 0;
		ret->directory = 1;
	}

	for (cp = ret->pattern; (cp = strchr(cp, '/')) != NULL; cp++)
		ret->slash_cnt++;

	return ret;
}

static void free_exclude(struct exclude_struct *ex)
{
	free(ex->pattern);
	memset(ex,0,sizeof(*ex));
	free(ex);
}


void free_exclude_list(struct exclude_struct ***listp)
{
	struct exclude_struct **list = *listp;

	if (verbose > 2)
		rprintf(FINFO,"clearing exclude list\n");

	if (!list)
		return;

	while (*list)
		free_exclude(*list++);

	free(*listp);
	*listp = NULL;
}

static int check_one_exclude(char *name, struct exclude_struct *ex,
                             int name_is_dir)
{
	char *p;
	int match_start = 0;
	char *pattern = ex->pattern;

	/* If the pattern does not have any slashes AND it does not have
	 * a "**" (which could match a slash), then we just match the
	 * name portion of the path. */
	if (!ex->slash_cnt && !(ex->match_flags & MATCHFLG_WILD2)) {
		if ((p = strrchr(name,'/')) != NULL)
			name = p+1;
	}
	else if ((ex->match_flags & MATCHFLG_ABS_PATH) && *name != '/') {
		static char full_name[MAXPATHLEN];
		extern char curr_dir[];
		int plus = curr_dir[1] == '\0'? 1 : 0;
		snprintf(full_name, sizeof full_name,
			 "%s/%s", curr_dir+plus, name);
		name = full_name;
	}

	if (!name[0]) return 0;

	if (ex->directory && !name_is_dir) return 0;

	if (*pattern == '/') {
		match_start = 1;
		pattern++;
		if (*name == '/')
			name++;
	}

	if (ex->match_flags & MATCHFLG_WILD) {
		/* A non-anchored match with an infix slash and no "**"
		 * needs to match the last slash_cnt+1 name elements. */
		if (!match_start && ex->slash_cnt &&
		    !(ex->match_flags & MATCHFLG_WILD2)) {
			int cnt = ex->slash_cnt + 1;
			for (p = name + strlen(name) - 1; p >= name; p--) {
				if (*p == '/' && !--cnt)
					break;
			}
			name = p+1;
		}
		if (wildmatch(pattern, name))
			return 1;
		if (ex->match_flags & MATCHFLG_WILD2_PREFIX) {
			/* If the **-prefixed pattern has a '/' as the next
			 * character, then try to match the rest of the
			 * pattern at the root. */
			if (pattern[2] == '/' && wildmatch(pattern+3, name))
				return 1;
		}
		else if (!match_start && ex->match_flags & MATCHFLG_WILD2) {
			/* A non-anchored match with an infix or trailing "**"
			 * (but not a prefixed "**") needs to try matching
			 * after every slash. */
			while ((name = strchr(name, '/')) != NULL) {
				name++;
				if (wildmatch(pattern, name))
					return 1;
			}
		}
	} else if (match_start) {
		if (strcmp(name,pattern) == 0)
			return 1;
	} else {
		int l1 = strlen(name);
		int l2 = strlen(pattern);
		if (l2 <= l1 &&
		    strcmp(name+(l1-l2),pattern) == 0 &&
		    (l1==l2 || name[l1-(l2+1)] == '/')) {
			return 1;
		}
	}

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
