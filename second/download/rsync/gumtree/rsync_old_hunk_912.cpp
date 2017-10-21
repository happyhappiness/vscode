		}
	}

	if (!(ret = new0(struct filter_struct)))
		out_of_memory("add_rule");

	if (!(mflags & (MATCHFLG_ABS_PATH | MATCHFLG_MERGE_FILE))
	 && ((xflags & (XFLG_ANCHORED2ABS|XFLG_ABS_IF_SLASH) && *pat == '/')
	  || (xflags & XFLG_ABS_IF_SLASH && strchr(pat, '/') != NULL))) {
		mflags |= MATCHFLG_ABS_PATH;
		if (*pat == '/')
			ex_len = dirbuf_len - module_dirlen - 1;
		else
			ex_len = 0;
	} else
		ex_len = 0;
	if (!(ret->pattern = new_array(char, ex_len + pat_len + 1)))
		out_of_memory("add_rule");
	if (ex_len)
		memcpy(ret->pattern, dirbuf + module_dirlen, ex_len);
	strlcpy(ret->pattern + ex_len, pat, pat_len + 1);
	pat_len += ex_len;

	if (strpbrk(ret->pattern, "*[?")) {
		mflags |= MATCHFLG_WILD;
		if ((cp = strstr(ret->pattern, "**")) != NULL) {
			mflags |= MATCHFLG_WILD2;
			/* If the pattern starts with **, note that. */
