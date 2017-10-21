 * The easiest way to handle this is to simply truncate the list after the
 * tail item and then free the local list from the head.  When inheriting
 * the list for a new local dir, we just save off the filter_list_struct
 * values (so we can pop back to them later) and set the tail to NULL.
 */

static void free_filter(struct filter_struct *ex)
{
	if (ex->match_flags & MATCHFLG_PERDIR_MERGE) {
		free(ex->u.mergelist->debug_type);
		free(ex->u.mergelist);
		mergelist_cnt--;
	}
	free(ex->pattern);
	free(ex);
}

/* Build a filter structure given a filter pattern.  The value in "pat"
 * is not null-terminated. */
static void add_rule(struct filter_list_struct *listp, const char *pat,
		     unsigned int pat_len, uint32 mflags, int xflags)
{
	struct filter_struct *ret;
	const char *cp;
	unsigned int pre_len, suf_len, slash_cnt = 0;

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

	if (!(ret = new0(struct filter_struct)))
		out_of_memory("add_rule");

	if (pat_len > 1 && pat[pat_len-1] == '/') {
		pat_len--;
		mflags |= MATCHFLG_DIRECTORY;
	}

	for (cp = pat; cp < pat + pat_len; cp++) {
		if (*cp == '/')
			slash_cnt++;
	}

	if (!(mflags & (MATCHFLG_ABS_PATH | MATCHFLG_MERGE_FILE))
	 && ((xflags & (XFLG_ANCHORED2ABS|XFLG_ABS_IF_SLASH) && *pat == '/')
	  || (xflags & XFLG_ABS_IF_SLASH && slash_cnt))) {
		mflags |= MATCHFLG_ABS_PATH;
		if (*pat == '/')
			pre_len = dirbuf_len - module_dirlen - 1;
		else
			pre_len = 0;
	} else
		pre_len = 0;

	/* The daemon wants dir-exclude rules to get an appended "/" + "***". */
	if (xflags & XFLG_DIR2WILD3
	 && BITS_SETnUNSET(mflags, MATCHFLG_DIRECTORY, MATCHFLG_INCLUDE)) {
		mflags &= ~MATCHFLG_DIRECTORY;
		suf_len = sizeof SLASH_WILD3_SUFFIX - 1;
	} else
		suf_len = 0;

	if (!(ret->pattern = new_array(char, pre_len + pat_len + suf_len + 1)))
		out_of_memory("add_rule");
	if (pre_len) {
		memcpy(ret->pattern, dirbuf + module_dirlen, pre_len);
		for (cp = ret->pattern; cp < ret->pattern + pre_len; cp++) {
			if (*cp == '/')
				slash_cnt++;
		}
	}
	strlcpy(ret->pattern + pre_len, pat, pat_len + 1);
	pat_len += pre_len;
	if (suf_len) {
		memcpy(ret->pattern + pat_len, SLASH_WILD3_SUFFIX, suf_len+1);
		pat_len += suf_len;
		slash_cnt++;
	}

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
	} else
		ret->u.slash_cnt = slash_cnt;

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
