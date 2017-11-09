const char *find_filename_suffix(const char *fn, int fn_len, int *len_ptr)
{
	const char *suf, *s;
	BOOL had_tilde;
	int s_len;

	/* One or more dots at the start aren't a suffix. */
	while (fn_len && *fn == '.') fn++, fn_len--;

	/* Ignore the ~ in a "foo~" filename. */
	if (fn_len > 1 && fn[fn_len-1] == '~')
		fn_len--, had_tilde = True;
	else
		had_tilde = False;

	/* Assume we don't find an suffix. */
	suf = "";
	*len_ptr = 0;

	/* Find the last significant suffix. */
	for (s = fn + fn_len; fn_len > 1; ) {
		while (*--s != '.' && s != fn) {}
		if (s == fn)
			break;
		s_len = fn_len - (s - fn);
		fn_len = s - fn;
		if (s_len == 4) {
			if (strcmp(s+1, "bak") == 0
			 || strcmp(s+1, "old") == 0)
				continue;
		} else if (s_len == 5) {
			if (strcmp(s+1, "orig") == 0)
				continue;
		} else if (s_len > 2 && had_tilde
		    && s[1] == '~' && isDigit(s + 2))
			continue;
		*len_ptr = s_len;
		suf = s;
		if (s_len == 1)
			break;
		/* Determine if the suffix is all digits. */
		for (s++, s_len--; s_len > 0; s++, s_len--) {
			if (!isDigit(s))
				return suf;
		}
		/* An all-digit suffix may not be that signficant. */
		s = suf;
	}

	return suf;
}