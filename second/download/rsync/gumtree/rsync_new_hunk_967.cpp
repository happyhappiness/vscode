 * The easiest way to handle this is to simply truncate the list after the
 * tail item and then free the local list from the head.  When inheriting
 * the list for a new local dir, we just save off the filter_list_struct
 * values (so we can pop back to them later) and set the tail to NULL.
 */

static void teardown_mergelist(filter_rule *ex)
{
	if (DEBUG_GTE(FILTER, 2)) {
		rprintf(FINFO, "[%s] deactivating mergelist #%d%s\n",
			who_am_i(), mergelist_cnt - 1,
			ex->u.mergelist->debug_type);
	}

	/* We should deactivate mergelists in LIFO order. */
	assert(mergelist_cnt > 0);
	assert(ex == mergelist_parents[mergelist_cnt - 1]);

	/* The parent_dirscan filters should have been freed. */
	assert(ex->u.mergelist->parent_dirscan_head == NULL);

	free(ex->u.mergelist->debug_type);
	free(ex->u.mergelist);
	mergelist_cnt--;
}

static void free_filter(filter_rule *ex)
{
	free(ex->pattern);
	free(ex);
}

static void free_filters(filter_rule *head)
{
	filter_rule *rev_head = NULL;

	/* Reverse the list so we deactivate mergelists in the proper LIFO
	 * order. */
	while (head) {
		filter_rule *next = head->next;
		head->next = rev_head;
		rev_head = head;
		head = next;
	}

	while (rev_head) {
		filter_rule *prev = rev_head->next;
		/* Tear down mergelists here, not in free_filter, so that we
		 * affect only real filter lists and not temporarily allocated
		 * filters. */
		if (rev_head->rflags & FILTRULE_PERDIR_MERGE)
			teardown_mergelist(rev_head);
		free_filter(rev_head);
		rev_head = prev;
	}
}

/* Build a filter structure given a filter pattern.  The value in "pat"
 * is not null-terminated.  "rule" is either held or freed, so the
 * caller should not free it. */
static void add_rule(filter_rule_list *listp, const char *pat, unsigned int pat_len,
		     filter_rule *rule, int xflags)
{
	const char *cp;
	unsigned int pre_len, suf_len, slash_cnt = 0;

	if (DEBUG_GTE(FILTER, 2)) {
		rprintf(FINFO, "[%s] add_rule(%s%.*s%s)%s\n",
			who_am_i(), get_rule_prefix(rule, pat, 0, NULL),
			(int)pat_len, pat,
			(rule->rflags & FILTRULE_DIRECTORY) ? "/" : "",
			listp->debug_type);
	}

	/* These flags also indicate that we're reading a list that
	 * needs to be filtered now, not post-filtered later. */
	if (xflags & (XFLG_ANCHORED2ABS|XFLG_ABS_IF_SLASH)
		&& (rule->rflags & FILTRULES_SIDES)
			== (am_sender ? FILTRULE_RECEIVER_SIDE : FILTRULE_SENDER_SIDE)) {
		/* This filter applies only to the other side.  Drop it. */
		free_filter(rule);
		return;
	}

	if (pat_len > 1 && pat[pat_len-1] == '/') {
		pat_len--;
		rule->rflags |= FILTRULE_DIRECTORY;
	}

	for (cp = pat; cp < pat + pat_len; cp++) {
		if (*cp == '/')
			slash_cnt++;
	}

	if (!(rule->rflags & (FILTRULE_ABS_PATH | FILTRULE_MERGE_FILE))
	 && ((xflags & (XFLG_ANCHORED2ABS|XFLG_ABS_IF_SLASH) && *pat == '/')
	  || (xflags & XFLG_ABS_IF_SLASH && slash_cnt))) {
		rule->rflags |= FILTRULE_ABS_PATH;
		if (*pat == '/')
			pre_len = dirbuf_len - module_dirlen - 1;
		else
			pre_len = 0;
	} else
		pre_len = 0;

	/* The daemon wants dir-exclude rules to get an appended "/" + "***". */
	if (xflags & XFLG_DIR2WILD3
	 && BITS_SETnUNSET(rule->rflags, FILTRULE_DIRECTORY, FILTRULE_INCLUDE)) {
		rule->rflags &= ~FILTRULE_DIRECTORY;
		suf_len = sizeof SLASH_WILD3_SUFFIX - 1;
	} else
		suf_len = 0;

	if (!(rule->pattern = new_array(char, pre_len + pat_len + suf_len + 1)))
		out_of_memory("add_rule");
	if (pre_len) {
		memcpy(rule->pattern, dirbuf + module_dirlen, pre_len);
		for (cp = rule->pattern; cp < rule->pattern + pre_len; cp++) {
			if (*cp == '/')
				slash_cnt++;
		}
	}
	strlcpy(rule->pattern + pre_len, pat, pat_len + 1);
	pat_len += pre_len;
	if (suf_len) {
		memcpy(rule->pattern + pat_len, SLASH_WILD3_SUFFIX, suf_len+1);
		pat_len += suf_len;
		slash_cnt++;
	}

	if (strpbrk(rule->pattern, "*[?")) {
		rule->rflags |= FILTRULE_WILD;
		if ((cp = strstr(rule->pattern, "**")) != NULL) {
			rule->rflags |= FILTRULE_WILD2;
			/* If the pattern starts with **, note that. */
			if (cp == rule->pattern)
				rule->rflags |= FILTRULE_WILD2_PREFIX;
			/* If the pattern ends with ***, note that. */
			if (pat_len >= 3
			 && rule->pattern[pat_len-3] == '*'
			 && rule->pattern[pat_len-2] == '*'
			 && rule->pattern[pat_len-1] == '*')
				rule->rflags |= FILTRULE_WILD3_SUFFIX;
		}
	}

	if (rule->rflags & FILTRULE_PERDIR_MERGE) {
		filter_rule_list *lp;
		unsigned int len;
		int i;

		if ((cp = strrchr(rule->pattern, '/')) != NULL)
			cp++;
		else
			cp = rule->pattern;

		/* If the local merge file was already mentioned, don't
		 * add it again. */
		for (i = 0; i < mergelist_cnt; i++) {
			filter_rule *ex = mergelist_parents[i];
			const char *s = strrchr(ex->pattern, '/');
			if (s)
				s++;
			else
				s = ex->pattern;
			len = strlen(s);
			if (len == pat_len - (cp - rule->pattern) && memcmp(s, cp, len) == 0) {
				free_filter(rule);
				return;
			}
		}

		if (!(lp = new_array(filter_rule_list, 1)))
			out_of_memory("add_rule");
		lp->head = lp->tail = lp->parent_dirscan_head = NULL;
		if (asprintf(&lp->debug_type, " [per-dir %s]", cp) < 0)
			out_of_memory("add_rule");
		rule->u.mergelist = lp;

		if (mergelist_cnt == mergelist_size) {
			mergelist_size += 5;
			mergelist_parents = realloc_array(mergelist_parents,
						filter_rule *,
						mergelist_size);
			if (!mergelist_parents)
				out_of_memory("add_rule");
		}
		if (DEBUG_GTE(FILTER, 2)) {
			rprintf(FINFO, "[%s] activating mergelist #%d%s\n",
				who_am_i(), mergelist_cnt, lp->debug_type);
		}
		mergelist_parents[mergelist_cnt++] = rule;
	} else
		rule->u.slash_cnt = slash_cnt;

	if (!listp->tail) {
		rule->next = listp->head;
		listp->head = listp->tail = rule;
	} else {
		rule->next = listp->tail->next;
		listp->tail->next = rule;
		listp->tail = rule;
	}
}

static void clear_filter_list(filter_rule_list *listp)
{
	if (listp->tail) {
		/* Truncate any inherited items from the local list. */
		listp->tail->next = NULL;
		/* Now free everything that is left. */
		free_filters(listp->head);
	}

	listp->head = listp->tail = NULL;
}

/* This returns an expanded (absolute) filename for the merge-file name if
