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
