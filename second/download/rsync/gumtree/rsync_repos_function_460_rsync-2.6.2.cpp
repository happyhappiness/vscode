static int domatch(const unsigned char *p, const unsigned char *text)
{
    int matched, special;
    unsigned char ch, prev;

#ifdef WILD_TEST_ITERATIONS
    wildmatch_iteration_count++;
#endif

    for ( ; (ch = *p) != '\0'; text++, p++) {
	if (*text == '\0' && ch != '*')
	    return FALSE;
	switch (ch) {
	  case '\\':
	    /* Literal match with following character.  Note that the test
	     * in "default" handles the p[1] == '\0' failure case. */
	    ch = *++p;
	    /* FALLTHROUGH */
	  default:
	    if (*text != ch)
		return FALSE;
	    continue;
	  case '?':
	    /* Match anything but '/'. */
	    if (*text == '/')
		return FALSE;
	    continue;
	  case '*':
	    if (*++p == '*') {
		while (*++p == '*') {}
		special = TRUE;
	    }
	    else
		special = FALSE;
	    if (*p == '\0') {
		/* Trailing "**" matches everything.  Trailing "*" matches
		 * only if there are no more slash characters. */
		return special? TRUE : strchr((char*)text, '/') == NULL;
	    }
	    for ( ; *text; text++) {
		if ((matched = domatch(p, text)) != FALSE) {
		    if (!special || matched != ABORT_TO_STARSTAR)
			return matched;
		}
		else if (!special && *text == '/')
		    return ABORT_TO_STARSTAR;
	    }
	    return ABORT_ALL;
	  case '[':
	    ch = *++p;
#ifdef NEGATE_CLASS2
	    if (ch == NEGATE_CLASS2)
		ch = NEGATE_CLASS;
#endif
	    /* Assign literal TRUE/FALSE because of "matched" comparison. */
	    special = ch == NEGATE_CLASS? TRUE : FALSE;
	    if (special) {
		/* Inverted character class. */
		ch = *++p;
	    }
	    prev = 0;
	    matched = FALSE;
	    do {
		if (!ch)
		    return ABORT_ALL;
		if (ch == '\\') {
		    ch = *++p;
		    if (!ch)
			return ABORT_ALL;
		    if (*text == ch)
			matched = TRUE;
		}
		else if (ch == '-' && prev && p[1] && p[1] != ']') {
		    ch = *++p;
		    if (ch == '\\') {
			ch = *++p;
			if (!ch)
			    return ABORT_ALL;
		    }
		    if (*text <= ch && *text >= prev)
			matched = TRUE;
		    ch = 0; /* This makes "prev" get set to 0. */
		}
		else if (ch == '[' && p[1] == ':') {
		    const unsigned char *s = p += 2;
		    int i;
		    while ((ch = *p) && ch != ']') p++;
		    if (!ch)
			return ABORT_ALL;
		    i = p - s - 1;
		    if (i < 0 || p[-1] != ':') {
			/* Didn't find ":]", so treat like a normal set. */
			p = s - 2;
			ch = '[';
			if (*text == ch)
			    matched = TRUE;
			continue;
		    }
		    if (CC_EQ(s,i, "alnum")) {
			if (ISALNUM(*text))
			    matched = TRUE;
		    }
		    else if (CC_EQ(s,i, "alpha")) {
			if (ISALPHA(*text))
			    matched = TRUE;
		    }
		    else if (CC_EQ(s,i, "blank")) {
			if (ISBLANK(*text))
			    matched = TRUE;
		    }
		    else if (CC_EQ(s,i, "cntrl")) {
			if (ISCNTRL(*text))
			    matched = TRUE;
		    }
		    else if (CC_EQ(s,i, "digit")) {
			if (ISDIGIT(*text))
			    matched = TRUE;
		    }
		    else if (CC_EQ(s,i, "graph")) {
			if (ISGRAPH(*text))
			    matched = TRUE;
		    }
		    else if (CC_EQ(s,i, "lower")) {
			if (ISLOWER(*text))
			    matched = TRUE;
		    }
		    else if (CC_EQ(s,i, "print")) {
			if (ISPRINT(*text))
			    matched = TRUE;
		    }
		    else if (CC_EQ(s,i, "punct")) {
			if (ISPUNCT(*text))
			    matched = TRUE;
		    }
		    else if (CC_EQ(s,i, "space")) {
			if (ISSPACE(*text))
			    matched = TRUE;
		    }
		    else if (CC_EQ(s,i, "upper")) {
			if (ISUPPER(*text))
			    matched = TRUE;
		    }
		    else if (CC_EQ(s,i, "xdigit")) {
			if (ISXDIGIT(*text))
			    matched = TRUE;
		    }
		    else /* malformed [:class:] string */
			return ABORT_ALL;
		    ch = 0; /* This makes "prev" get set to 0. */
		}
		else if (*text == ch)
		    matched = TRUE;
	    } while (prev = ch, (ch = *++p) != ']');
	    if (matched == special || *text == '/')
		return FALSE;
	    continue;
	}
    }

    return *text == '\0';
}