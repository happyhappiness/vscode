static const char *rangematch(const char *pattern, int test, int flags)
{
    int negate, ok;
    char c, c2;

    /*
     * A bracket expression starting with an unquoted circumflex
     * character produces unspecified results (IEEE 1003.2-1992,
     * 3.13.2).  This implementation treats it like '!', for
     * consistency with the regular expression syntax.
     * J.T. Conklin (conklin@ngai.kaleida.com)
     */
    if ((negate = (*pattern == '!' || *pattern == '^'))) {
	++pattern;
    }

    for (ok = 0; (c = *pattern++) != ']';) {
        if (c == '\\' && !(flags & APR_FNM_NOESCAPE)) {
	    c = *pattern++;
	}
	if (c == EOS) {
	    return (NULL);
	}
	if (*pattern == '-' && (c2 = *(pattern + 1)) != EOS && c2 != ']') {
	    pattern += 2;
	    if (c2 == '\\' && !(flags & APR_FNM_NOESCAPE)) {
		c2 = *pattern++;
	    }
	    if (c2 == EOS) {
		return (NULL);
	    }
	    if ((c <= test && test <= c2)
		|| ((flags & APR_FNM_CASE_BLIND)
		    && ((apr_tolower(c) <= apr_tolower(test))
			&& (apr_tolower(test) <= apr_tolower(c2))))) {
		ok = 1;
	    }
	}
	else if ((c == test)
		 || ((flags & APR_FNM_CASE_BLIND)
		     && (apr_tolower(c) == apr_tolower(test)))) {
	    ok = 1;
	}
    }
    return (ok == negate ? NULL : pattern);
}