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