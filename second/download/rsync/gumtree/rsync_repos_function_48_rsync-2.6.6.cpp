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
		} else if (*s == '!')
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