
	if (pat_len > 1 && ret->pattern[pat_len-1] == '/') {
		ret->pattern[pat_len-1] = 0;
		mflags |= MATCHFLG_DIRECTORY;
	}

	if (mflags & MATCHFLG_PERDIR_MERGE) {
		struct filter_list_struct *lp;
		unsigned int len;
		int i;

		if ((cp = strrchr(ret->pattern, '/')) != NULL)
			cp++;
		else
			cp = ret->pattern;

		/* If the local merge file was already mentioned, don't
		 * add it again. */
		for (i = 0; i < mergelist_cnt; i++) {
			struct filter_struct *ex = mergelist_parents[i];
			const char *s = strrchr(ex->pattern, '/');
			if (s)
				s++;
			else
				s = ex->pattern;
			len = strlen(s);
			if (len == pat_len - (cp - ret->pattern)
			    && memcmp(s, cp, len) == 0) {
				free_filter(ret);
				return;
			}
		}

		if (!(lp = new_array(struct filter_list_struct, 1)))
			out_of_memory("add_rule");
		lp->head = lp->tail = NULL;
		if (asprintf(&lp->debug_type, " [per-dir %s]", cp) < 0)
			out_of_memory("add_rule");
		ret->u.mergelist = lp;

		if (mergelist_cnt == mergelist_size) {
			mergelist_size += 5;
			mergelist_parents = realloc_array(mergelist_parents,
						struct filter_struct *,
						mergelist_size);
			if (!mergelist_parents)
				out_of_memory("add_rule");
		}
		mergelist_parents[mergelist_cnt++] = ret;
	} else {
		for (cp = ret->pattern; (cp = strchr(cp, '/')) != NULL; cp++)
			ret->u.slash_cnt++;
	}

	ret->match_flags = mflags;

	if (!listp->tail) {
		ret->next = listp->head;
		listp->head = listp->tail = ret;
	} else {
		ret->next = listp->tail->next;
		listp->tail->next = ret;
		listp->tail = ret;
	}
}

static void clear_filter_list(struct filter_list_struct *listp)
{
	if (listp->tail) {
		struct filter_struct *ent, *next;
		/* Truncate any inherited items from the local list. */
		listp->tail->next = NULL;
		/* Now free everything that is left. */
		for (ent = listp->head; ent; ent = next) {
			next = ent->next;
			free_filter(ent);
		}
	}

	listp->head = listp->tail = NULL;
}

/* This returns an expanded (absolute) filename for the merge-file name if
 * the name has any slashes in it OR if the parent_dirscan var is True;
 * otherwise it returns the original merge_file name.  If the len_ptr value
 * is non-NULL the merge_file name is limited by the referenced length
 * value and will be updated with the length of the resulting name.  We
 * always return a name that is null terminated, even if the merge_file
 * name was not. */
static char *parse_merge_name(const char *merge_file, unsigned int *len_ptr,
			      unsigned int prefix_skip)
{
	static char buf[MAXPATHLEN];
	char *fn, tmpbuf[MAXPATHLEN];
	unsigned int fn_len;

	if (!parent_dirscan && *merge_file != '/') {
		/* Return the name unchanged it doesn't have any slashes. */
		if (len_ptr) {
			const char *p = merge_file + *len_ptr;
			while (--p > merge_file && *p != '/') {}
			if (p == merge_file) {
				strlcpy(buf, merge_file, *len_ptr + 1);
				return buf;
			}
		} else if (strchr(merge_file, '/') == NULL)
			return (char *)merge_file;
	}

	fn = *merge_file == '/' ? buf : tmpbuf;
	if (sanitize_paths) {
		const char *r = prefix_skip ? "/" : NULL;
		/* null-terminate the name if it isn't already */
		if (len_ptr && merge_file[*len_ptr]) {
			char *to = fn == buf ? tmpbuf : buf;
			strlcpy(to, merge_file, *len_ptr + 1);
			merge_file = to;
		}
		if (!sanitize_path(fn, merge_file, r, dirbuf_depth)) {
			rprintf(FERROR, "merge-file name overflows: %s\n",
				safe_fname(merge_file));
			return NULL;
		}
	} else {
		strlcpy(fn, merge_file, len_ptr ? *len_ptr + 1 : MAXPATHLEN);
		clean_fname(fn, 1);
	}
	
	fn_len = strlen(fn);
	if (fn == buf)
		goto done;

	if (dirbuf_len + fn_len >= MAXPATHLEN) {
		rprintf(FERROR, "merge-file name overflows: %s\n",
			safe_fname(fn));
		return NULL;
	}
	memcpy(buf, dirbuf + prefix_skip, dirbuf_len - prefix_skip);
	memcpy(buf + dirbuf_len - prefix_skip, fn, fn_len + 1);
	fn_len = clean_fname(buf, 1);

    done:
	if (len_ptr)
		*len_ptr = fn_len;
	return buf;
}

/* Sets the dirbuf and dirbuf_len values. */
void set_filter_dir(const char *dir, unsigned int dirlen)
{
	unsigned int len;
	if (*dir != '/') {
		memcpy(dirbuf, curr_dir, curr_dir_len);
		dirbuf[curr_dir_len] = '/';
		len = curr_dir_len + 1;
		if (len + dirlen >= MAXPATHLEN)
			dirlen = 0;
	} else
		len = 0;
	memcpy(dirbuf + len, dir, dirlen);
	dirbuf[dirlen + len] = '\0';
	dirbuf_len = clean_fname(dirbuf, 1);
	if (dirbuf_len > 1 && dirbuf[dirbuf_len-1] == '.'
	    && dirbuf[dirbuf_len-2] == '/')
		dirbuf_len -= 2;
	if (dirbuf_len != 1)
		dirbuf[dirbuf_len++] = '/';
	dirbuf[dirbuf_len] = '\0';
	if (sanitize_paths)
		dirbuf_depth = count_dir_elements(dirbuf + module_dirlen);
}

/* This routine takes a per-dir merge-file entry and finishes its setup.
 * If the name has a path portion then we check to see if it refers to a
 * parent directory of the first transfer dir.  If it does, we scan all the
 * dirs from that point through the parent dir of the transfer dir looking
 * for the per-dir merge-file in each one. */
static BOOL setup_merge_file(struct filter_struct *ex,
			     struct filter_list_struct *lp)
{
	char buf[MAXPATHLEN];
	char *x, *y, *pat = ex->pattern;
	unsigned int len;

	if (!(x = parse_merge_name(pat, NULL, 0)) || *x != '/')
		return 0;

	y = strrchr(x, '/');
	*y = '\0';
	ex->pattern = strdup(y+1);
	if (!*x)
		x = "/";
	if (*x == '/')
		strlcpy(buf, x, MAXPATHLEN);
	else
		pathjoin(buf, MAXPATHLEN, dirbuf, x);

	len = clean_fname(buf, 1);
	if (len != 1 && len < MAXPATHLEN-1) {
		buf[len++] = '/';
		buf[len] = '\0';
	}
	/* This ensures that the specified dir is a parent of the transfer. */
	for (x = buf, y = dirbuf; *x && *x == *y; x++, y++) {}
	if (*x)
		y += strlen(y); /* nope -- skip the scan */

	parent_dirscan = True;
	while (*y) {
		char save[MAXPATHLEN];
		strlcpy(save, y, MAXPATHLEN);
		*y = '\0';
		dirbuf_len = y - dirbuf;
		strlcpy(x, ex->pattern, MAXPATHLEN - (x - buf));
		parse_filter_file(lp, buf, ex->match_flags, XFLG_ANCHORED2ABS);
		if (ex->match_flags & MATCHFLG_NO_INHERIT)
			lp->head = NULL;
		lp->tail = NULL;
		strlcpy(y, save, MAXPATHLEN);
		while ((*x++ = *y++) != '/') {}
	}
	parent_dirscan = False;
	free(pat);
	return 1;
}

/* Each time rsync changes to a new directory it call this function to
 * handle all the per-dir merge-files.  The "dir" value is the current path
 * relative to curr_dir (which might not be null-terminated).  We copy it
 * into dirbuf so that we can easily append a file name on the end. */
void *push_local_filters(const char *dir, unsigned int dirlen)
{
	struct filter_list_struct *ap, *push;
	int i;

	set_filter_dir(dir, dirlen);

	if (!mergelist_cnt)
		return NULL;

	push = new_array(struct filter_list_struct, mergelist_cnt);
	if (!push)
		out_of_memory("push_local_filters");

	for (i = 0, ap = push; i < mergelist_cnt; i++) {
		memcpy(ap++, mergelist_parents[i]->u.mergelist,
		       sizeof (struct filter_list_struct));
	}

	/* Note: parse_filter_file() might increase mergelist_cnt, so keep
	 * this loop separate from the above loop. */
	for (i = 0; i < mergelist_cnt; i++) {
		struct filter_struct *ex = mergelist_parents[i];
		struct filter_list_struct *lp = ex->u.mergelist;

		if (verbose > 2) {
			rprintf(FINFO, "[%s] pushing filter list%s\n",
				who_am_i(), lp->debug_type);
		}

		lp->tail = NULL; /* Switch any local rules to inherited. */
		if (ex->match_flags & MATCHFLG_NO_INHERIT)
			lp->head = NULL;

		if (ex->match_flags & MATCHFLG_FINISH_SETUP) {
			ex->match_flags &= ~MATCHFLG_FINISH_SETUP;
			if (setup_merge_file(ex, lp))
				set_filter_dir(dir, dirlen);
		}

		if (strlcpy(dirbuf + dirbuf_len, ex->pattern,
		    MAXPATHLEN - dirbuf_len) < MAXPATHLEN - dirbuf_len) {
			parse_filter_file(lp, dirbuf, ex->match_flags,
					  XFLG_ANCHORED2ABS);
		} else {
			io_error |= IOERR_GENERAL;
			rprintf(FINFO,
			    "cannot add local filter rules in long-named directory: %s\n",
			    full_fname(dirbuf));
		}
		dirbuf[dirbuf_len] = '\0';
	}

	return (void*)push;
}

void pop_local_filters(void *mem)
{
	struct filter_list_struct *ap, *pop = (struct filter_list_struct*)mem;
	int i;

	for (i = mergelist_cnt; i-- > 0; ) {
		struct filter_struct *ex = mergelist_parents[i];
		struct filter_list_struct *lp = ex->u.mergelist;

		if (verbose > 2) {
			rprintf(FINFO, "[%s] popping filter list%s\n",
				who_am_i(), lp->debug_type);
		}

		clear_filter_list(lp);
	}

	if (!pop)
		return;

	for (i = 0, ap = pop; i < mergelist_cnt; i++) {
		memcpy(mergelist_parents[i]->u.mergelist, ap++,
		       sizeof (struct filter_list_struct));
	}

	free(pop);
}

static int rule_matches(char *name, struct filter_struct *ex, int name_is_dir)
{
	char *p, full_name[MAXPATHLEN];
	int match_start = 0;
	int ret_match = ex->match_flags & MATCHFLG_NEGATE ? 0 : 1;
	char *pattern = ex->pattern;

	if (!*name)
		return 0;

	/* If the pattern does not have any slashes AND it does not have
	 * a "**" (which could match a slash), then we just match the
	 * name portion of the path. */
	if (!ex->u.slash_cnt && !(ex->match_flags & MATCHFLG_WILD2)) {
		if ((p = strrchr(name,'/')) != NULL)
			name = p+1;
	}
	else if (ex->match_flags & MATCHFLG_ABS_PATH && *name != '/'
	    && curr_dir_len > module_dirlen + 1) {
		pathjoin(full_name, sizeof full_name,
			 curr_dir + module_dirlen + 1, name);
		name = full_name;
	}

	if (ex->match_flags & MATCHFLG_DIRECTORY && !name_is_dir)
		return !ret_match;

	if (*pattern == '/') {
		match_start = 1;
		pattern++;
		if (*name == '/')
			name++;
	}

	if (ex->match_flags & MATCHFLG_WILD) {
		/* A non-anchored match with an infix slash and no "**"
		 * needs to match the last slash_cnt+1 name elements. */
		if (!match_start && ex->u.slash_cnt
		    && !(ex->match_flags & MATCHFLG_WILD2)) {
			int cnt = ex->u.slash_cnt + 1;
			for (p = name + strlen(name) - 1; p >= name; p--) {
				if (*p == '/' && !--cnt)
					break;
			}
			name = p+1;
		}
		if (wildmatch(pattern, name))
			return ret_match;
		if (ex->match_flags & MATCHFLG_WILD2_PREFIX) {
			/* If the **-prefixed pattern has a '/' as the next
			 * character, then try to match the rest of the
			 * pattern at the root. */
			if (pattern[2] == '/' && wildmatch(pattern+3, name))
				return ret_match;
		}
		else if (!match_start && ex->match_flags & MATCHFLG_WILD2) {
			/* A non-anchored match with an infix or trailing "**"
			 * (but not a prefixed "**") needs to try matching
			 * after every slash. */
			while ((name = strchr(name, '/')) != NULL) {
				name++;
				if (wildmatch(pattern, name))
					return ret_match;
			}
		}
	} else if (match_start) {
		if (strcmp(name,pattern) == 0)
			return ret_match;
	} else {
		int l1 = strlen(name);
		int l2 = strlen(pattern);
		if (l2 <= l1 &&
		    strcmp(name+(l1-l2),pattern) == 0 &&
		    (l1==l2 || name[l1-(l2+1)] == '/')) {
			return ret_match;
		}
	}

	return !ret_match;
}


static void report_filter_result(char const *name,
                                 struct filter_struct const *ent,
                                 int name_is_dir, const char *type)
{
	/* If a trailing slash is present to match only directories,
	 * then it is stripped out by add_rule().  So as a special
	 * case we add it back in here. */

	if (verbose >= 2) {
		rprintf(FINFO, "[%s] %scluding %s %s because of pattern %s%s%s\n",
			who_am_i(),
			ent->match_flags & MATCHFLG_INCLUDE ? "in" : "ex",
			name_is_dir ? "directory" : "file", name, ent->pattern,
			ent->match_flags & MATCHFLG_DIRECTORY ? "/" : "", type);
	}
}


/*
 * Return -1 if file "name" is defined to be excluded by the specified
 * exclude list, 1 if it is included, and 0 if it was not matched.
 */
int check_filter(struct filter_list_struct *listp, char *name, int name_is_dir)
{
	struct filter_struct *ent;

	for (ent = listp->head; ent; ent = ent->next) {
		if (ent->match_flags & MATCHFLG_PERDIR_MERGE) {
			int rc = check_filter(ent->u.mergelist, name,
					      name_is_dir);
			if (rc)
				return rc;
			continue;
		}
		if (ent->match_flags & MATCHFLG_CVS_IGNORE) {
			int rc = check_filter(&cvs_filter_list, name,
					      name_is_dir);
			if (rc)
				return rc;
			continue;
		}
		if (rule_matches(name, ent, name_is_dir)) {
			report_filter_result(name, ent, name_is_dir,
					      listp->debug_type);
			return ent->match_flags & MATCHFLG_INCLUDE ? 1 : -1;
		}
	}

	return 0;
}

#define RULE_STRCMP(s,r) rule_strcmp((s), (r), sizeof (r) - 1)

static const uchar *rule_strcmp(const uchar *str, const char *rule, int rule_len)
{
	if (strncmp((char*)str, rule, rule_len) != 0)
		return NULL;
	if (isspace(str[rule_len]) || str[rule_len] == '_' || !str[rule_len])
		return str + rule_len - 1;
	if (str[rule_len] == ',')
		return str + rule_len;
	return NULL;
}

/* Get the next include/exclude arg from the string.  The token will not
 * be '\0' terminated, so use the returned length to limit the string.
 * Also, be sure to add this length to the returned pointer before passing
 * it back to ask for the next token.  This routine parses the "!" (list-
 * clearing) token and (depending on the mflags) the various prefixes.
 * The *mflags_ptr value will be set on exit to the new MATCHFLG_* bits
 * for the current token. */
static const char *parse_rule_tok(const char *p, uint32 mflags, int xflags,
				  unsigned int *len_ptr, uint32 *mflags_ptr)
{
	const uchar *s = (const uchar *)p;
	uint32 new_mflags;
	unsigned int len;

	if (mflags & MATCHFLG_WORD_SPLIT) {
		/* Skip over any initial whitespace. */
		while (isspace(*s))
			s++;
		/* Update to point to real start of rule. */
		p = (const char *)s;
	}
	if (!*s)
		return NULL;

	new_mflags = mflags & MATCHFLGS_FROM_CONTAINER;

	/* Figure out what kind of a filter rule "s" is pointing at.  Note
	 * that if MATCHFLG_NO_PREFIXES is set, the rule is either an include
	 * or an exclude based on the inheritance of the MATCHFLG_INCLUDE
	 * flag (above).  XFLG_OLD_PREFIXES indicates a compatibility mode
	 * for old include/exclude patterns where just "+ " and "- " are
	 * allowed as optional prefixes.  */
	if (mflags & MATCHFLG_NO_PREFIXES) {
		if (*s == '!' && mflags & MATCHFLG_CVS_IGNORE)
			new_mflags |= MATCHFLG_CLEAR_LIST; /* Tentative! */
	} else if (xflags & XFLG_OLD_PREFIXES) {
		if (*s == '-' && s[1] == ' ') {
			new_mflags &= ~MATCHFLG_INCLUDE;
			s += 2;
		} else if (*s == '+' && s[1] == ' ') {
			new_mflags |= MATCHFLG_INCLUDE;
			s += 2;
		}
		if (*s == '!')
			new_mflags |= MATCHFLG_CLEAR_LIST; /* Tentative! */
	} else {
		char ch = 0, *mods = "";
		switch (*s) {
		case 'c':
			if ((s = RULE_STRCMP(s, "clear")) != NULL)
				ch = '!';
			break;
		case 'd':
			if ((s = RULE_STRCMP(s, "dir-merge")) != NULL)
				ch = ':';
			break;
		case 'e':
			if ((s = RULE_STRCMP(s, "exclude")) != NULL)
				ch = '-';
			break;
		case 'h':
			if ((s = RULE_STRCMP(s, "hide")) != NULL)
				ch = 'H';
			break;
		case 'i':
			if ((s = RULE_STRCMP(s, "include")) != NULL)
				ch = '+';
			break;
		case 'm':
			if ((s = RULE_STRCMP(s, "merge")) != NULL)
				ch = '.';
			break;
		case 'p':
			if ((s = RULE_STRCMP(s, "protect")) != NULL)
				ch = 'P';
			break;
		case 'r':
			if ((s = RULE_STRCMP(s, "risk")) != NULL)
				ch = 'R';
			break;
		case 's':
			if ((s = RULE_STRCMP(s, "show")) != NULL)
				ch = 'S';
			break;

		default:
			ch = *s;
			if (s[1] == ',')
				s++;
			break;
		}
		switch (ch) {
		case ':':
			new_mflags |= MATCHFLG_PERDIR_MERGE
				    | MATCHFLG_FINISH_SETUP;
			/* FALL THROUGH */
		case '.':
			new_mflags |= MATCHFLG_MERGE_FILE;
			mods = MODIFIERS_INCL_EXCL MODIFIERS_MERGE_FILE;
			break;
		case '+':
			new_mflags |= MATCHFLG_INCLUDE;
			/* FALL THROUGH */
		case '-':
			mods = MODIFIERS_INCL_EXCL;
			break;
		case 'S':
			new_mflags |= MATCHFLG_INCLUDE;
			/* FALL THROUGH */
		case 'H':
			new_mflags |= MATCHFLG_SENDER_SIDE;
			mods = MODIFIERS_HIDE_PROTECT;
			break;
		case 'R':
			new_mflags |= MATCHFLG_INCLUDE;
			/* FALL THROUGH */
		case 'P':
			new_mflags |= MATCHFLG_RECEIVER_SIDE;
			mods = MODIFIERS_HIDE_PROTECT;
			break;
		case '!':
			new_mflags |= MATCHFLG_CLEAR_LIST;
			mods = NULL;
			break;
		default:
			rprintf(FERROR, "Unknown filter rule: `%s'\n", p);
			exit_cleanup(RERR_SYNTAX);
		}
		while (mods && *++s && *s != ' ' && *s != '_') {
			if (strchr(mods, *s) == NULL) {
				if (mflags & MATCHFLG_WORD_SPLIT && isspace(*s)) {
					s--;
					break;
				}
			    invalid:
				rprintf(FERROR,
					"invalid modifier sequence at '%c' in filter rule: %s\n",
					*s, p);
				exit_cleanup(RERR_SYNTAX);
			}
			switch (*s) {
			case '-':
				if (new_mflags & MATCHFLG_NO_PREFIXES)
				    goto invalid;
				new_mflags |= MATCHFLG_NO_PREFIXES;
				break;
			case '+':
				if (new_mflags & MATCHFLG_NO_PREFIXES)
				    goto invalid;
				new_mflags |= MATCHFLG_NO_PREFIXES
					    | MATCHFLG_INCLUDE;
				break;
			case '/':
				new_mflags |= MATCHFLG_ABS_PATH;
				break;
			case '!':
				new_mflags |= MATCHFLG_NEGATE;
				break;
			case 'C':
				if (new_mflags & MATCHFLG_NO_PREFIXES)
				    goto invalid;
				new_mflags |= MATCHFLG_NO_PREFIXES
					    | MATCHFLG_WORD_SPLIT
					    | MATCHFLG_NO_INHERIT
					    | MATCHFLG_CVS_IGNORE;
				break;
			case 'e':
				new_mflags |= MATCHFLG_EXCLUDE_SELF;
				break;
			case 'n':
				new_mflags |= MATCHFLG_NO_INHERIT;
				break;
			case 'r':
				new_mflags |= MATCHFLG_RECEIVER_SIDE;
				break;
			case 's':
				new_mflags |= MATCHFLG_SENDER_SIDE;
				break;
			case 'w':
				new_mflags |= MATCHFLG_WORD_SPLIT;
				break;
			}
		}
		if (*s)
			s++;
	}

	if (mflags & MATCHFLG_WORD_SPLIT) {
		const uchar *cp = s;
		/* Token ends at whitespace or the end of the string. */
		while (!isspace(*cp) && *cp != '\0')
			cp++;
		len = cp - s;
	} else
		len = strlen((char*)s);

	if (new_mflags & MATCHFLG_CLEAR_LIST) {
		if (!(xflags & XFLG_OLD_PREFIXES) && len) {
			rprintf(FERROR,
				"'!' rule has trailing characters: %s\n", p);
			exit_cleanup(RERR_SYNTAX);
		}
		if (len > 1)
			new_mflags &= ~MATCHFLG_CLEAR_LIST;
	} else if (!len && !(new_mflags & MATCHFLG_CVS_IGNORE)) {
		rprintf(FERROR, "unexpected end of filter rule: %s\n", p);
		exit_cleanup(RERR_SYNTAX);
	}

	*len_ptr = len;
	*mflags_ptr = new_mflags;
	return (const char *)s;
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

static void get_cvs_excludes(uint32 mflags)
{
	char *p, fname[MAXPATHLEN];
	static int initialized = 0;

	if (initialized)
		return;
	initialized = 1;

	parse_rule(&cvs_filter_list, default_cvsignore, mflags, 0);

	p = module_id >= 0 && lp_use_chroot(module_id) ? "/" : getenv("HOME");
	if (p && pathjoin(fname, MAXPATHLEN, p, ".cvsignore") < MAXPATHLEN)
		parse_filter_file(&cvs_filter_list, fname, mflags, 0);

	parse_rule(&cvs_filter_list, getenv("CVSIGNORE"), mflags, 0);
}


void parse_rule(struct filter_list_struct *listp, const char *pattern,
		uint32 mflags, int xflags)
{
	unsigned int pat_len;
	uint32 new_mflags;
	const char *cp, *p;

	if (!pattern)
		return;

	while (1) {
		/* Remember that the returned string is NOT '\0' terminated! */
		cp = parse_rule_tok(pattern, mflags, xflags,
				    &pat_len, &new_mflags);
		if (!cp)
			break;
		if (pat_len >= MAXPATHLEN) {
			rprintf(FERROR, "discarding over-long filter: %s\n",
				cp);
			continue;
		}
		pattern = cp + pat_len;

		if (new_mflags & MATCHFLG_CLEAR_LIST) {
			if (verbose > 2) {
				rprintf(FINFO,
					"[%s] clearing filter list%s\n",
					who_am_i(), listp->debug_type);
			}
			clear_filter_list(listp);
			continue;
		}

		if (new_mflags & MATCHFLG_MERGE_FILE) {
			unsigned int len;
			if (!pat_len) {
				cp = ".cvsignore";
				pat_len = 10;
			}
			len = pat_len;
			if (new_mflags & MATCHFLG_EXCLUDE_SELF) {
				const char *name = strrchr(cp, '/');
				if (name)
					len -= ++name - cp;
				else
					name = cp;
				add_rule(listp, name, len, 0, 0);
				new_mflags &= ~MATCHFLG_EXCLUDE_SELF;
				len = pat_len;
			}
			if (new_mflags & MATCHFLG_PERDIR_MERGE) {
				if (parent_dirscan) {
					if (!(p = parse_merge_name(cp, &len,
								module_dirlen)))
						continue;
					add_rule(listp, p, len, new_mflags, 0);
					continue;
				}
			} else {
				if (!(p = parse_merge_name(cp, &len, 0)))
					continue;
				parse_filter_file(listp, p, new_mflags,
						  XFLG_FATAL_ERRORS);
				continue;
			}
		}

		add_rule(listp, cp, pat_len, new_mflags, xflags);

		if (new_mflags & MATCHFLG_CVS_IGNORE
		    && !(new_mflags & MATCHFLG_MERGE_FILE))
			get_cvs_excludes(new_mflags);
	}
}


void parse_filter_file(struct filter_list_struct *listp, const char *fname,
		       uint32 mflags, int xflags)
{
	FILE *fp;
	char line[MAXPATHLEN+MAX_RULE_PREFIX+1]; /* +1 for trailing slash. */
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
			who_am_i(), safe_fname(fname), mflags, xflags,
			fp ? "" : " [not found]");
	}

	if (!fp) {
		if (xflags & XFLG_FATAL_ERRORS) {
			rsyserr(FERROR, errno,
				"failed to open %sclude file %s",
				mflags & MATCHFLG_INCLUDE ? "in" : "ex",
				safe_fname(fname));
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
