static void add_rule(struct filter_list_struct *listp, const char *pat,
		     unsigned int pat_len, uint32 mflags, int xflags)
{
	struct filter_struct *ret;
	const char *cp;
	unsigned int ex_len;

	if (verbose > 2) {
		rprintf(FINFO, "[%s] add_rule(%s%.*s%s)%s\n",
			who_am_i(), get_rule_prefix(mflags, pat, 0, NULL),
			(int)pat_len, pat,
			(mflags & MATCHFLG_DIRECTORY) ? "/" : "",
			listp->debug_type);
	}

	/* These flags also indicate that we're reading a list that
	 * needs to be filtered now, not post-filtered later. */
	if (xflags & (XFLG_ANCHORED2ABS|XFLG_ABS_IF_SLASH)) {
		uint32 mf = mflags & (MATCHFLG_RECEIVER_SIDE|MATCHFLG_SENDER_SIDE);
		if (am_sender) {
			if (mf == MATCHFLG_RECEIVER_SIDE)
				return;
		} else {
			if (mf == MATCHFLG_SENDER_SIDE)
				return;
		}
	}

	if (!(ret = new(struct filter_struct)))
		out_of_memory("add_rule");
	memset(ret, 0, sizeof ret[0]);

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
			if (cp == ret->pattern)
				mflags |= MATCHFLG_WILD2_PREFIX;
			/* If the pattern ends with ***, note that. */
			if (pat_len >= 3
			 && ret->pattern[pat_len-3] == '*'
			 && ret->pattern[pat_len-2] == '*'
			 && ret->pattern[pat_len-1] == '*')
				mflags |= MATCHFLG_WILD3_SUFFIX;
		}
	}

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