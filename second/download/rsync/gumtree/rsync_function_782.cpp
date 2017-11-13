static void make_exclude(struct exclude_list_struct *listp, const char *pat,
			 unsigned int pat_len, unsigned int mflags)
{
	struct exclude_struct *ret;
	const char *cp;
	unsigned int ex_len;

	ret = new(struct exclude_struct);
	if (!ret)
		out_of_memory("make_exclude");

	memset(ret, 0, sizeof ret[0]);

	if (exclude_path_prefix)
		mflags |= MATCHFLG_ABS_PATH;
	if (exclude_path_prefix && *pat == '/')
		ex_len = strlen(exclude_path_prefix);
	else
		ex_len = 0;
	ret->pattern = new_array(char, ex_len + pat_len + 1);
	if (!ret->pattern)
		out_of_memory("make_exclude");
	if (ex_len)
		memcpy(ret->pattern, exclude_path_prefix, ex_len);
	strlcpy(ret->pattern + ex_len, pat, pat_len + 1);
	pat_len += ex_len;

	if (strpbrk(ret->pattern, "*[?")) {
		mflags |= MATCHFLG_WILD;
		if ((cp = strstr(ret->pattern, "**")) != NULL) {
			mflags |= MATCHFLG_WILD2;
			/* If the pattern starts with **, note that. */
			if (cp == ret->pattern)
				mflags |= MATCHFLG_WILD2_PREFIX;
		}
	}

	if (pat_len > 1 && ret->pattern[pat_len-1] == '/') {
		ret->pattern[pat_len-1] = 0;
		mflags |= MATCHFLG_DIRECTORY;
	}

	for (cp = ret->pattern; (cp = strchr(cp, '/')) != NULL; cp++)
		ret->slash_cnt++;

	ret->match_flags = mflags;

	if (!listp->tail)
		listp->head = listp->tail = ret;
	else {
		listp->tail->next = ret;
		listp->tail = ret;
	}
}