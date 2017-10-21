  * The easiest way to handle this is to simply truncate the list after the
  * tail item and then free the local list from the head.  When inheriting
  * the list for a new local dir, we just save off the filter_list_struct
  * values (so we can pop back to them later) and set the tail to NULL.
  */
 
-static void free_filter(struct filter_struct *ex)
+static void teardown_mergelist(filter_rule *ex)
 {
-	if (ex->match_flags & MATCHFLG_PERDIR_MERGE) {
-		free(ex->u.mergelist->debug_type);
-		free(ex->u.mergelist);
-		mergelist_cnt--;
+	if (DEBUG_GTE(FILTER, 2)) {
+		rprintf(FINFO, "[%s] deactivating mergelist #%d%s\n",
+			who_am_i(), mergelist_cnt - 1,
+			ex->u.mergelist->debug_type);
 	}
+
+	/* We should deactivate mergelists in LIFO order. */
+	assert(mergelist_cnt > 0);
+	assert(ex == mergelist_parents[mergelist_cnt - 1]);
+
+	/* The parent_dirscan filters should have been freed. */
+	assert(ex->u.mergelist->parent_dirscan_head == NULL);
+
+	free(ex->u.mergelist->debug_type);
+	free(ex->u.mergelist);
+	mergelist_cnt--;
+}
+
+static void free_filter(filter_rule *ex)
+{
 	free(ex->pattern);
 	free(ex);
 }
 
+static void free_filters(filter_rule *head)
+{
+	filter_rule *rev_head = NULL;
+
+	/* Reverse the list so we deactivate mergelists in the proper LIFO
+	 * order. */
+	while (head) {
+		filter_rule *next = head->next;
+		head->next = rev_head;
+		rev_head = head;
+		head = next;
+	}
+
+	while (rev_head) {
+		filter_rule *prev = rev_head->next;
+		/* Tear down mergelists here, not in free_filter, so that we
+		 * affect only real filter lists and not temporarily allocated
+		 * filters. */
+		if (rev_head->rflags & FILTRULE_PERDIR_MERGE)
+			teardown_mergelist(rev_head);
+		free_filter(rev_head);
+		rev_head = prev;
+	}
+}
+
 /* Build a filter structure given a filter pattern.  The value in "pat"
- * is not null-terminated. */
-static void add_rule(struct filter_list_struct *listp, const char *pat,
-		     unsigned int pat_len, uint32 mflags, int xflags)
+ * is not null-terminated.  "rule" is either held or freed, so the
+ * caller should not free it. */
+static void add_rule(filter_rule_list *listp, const char *pat, unsigned int pat_len,
+		     filter_rule *rule, int xflags)
 {
-	struct filter_struct *ret;
 	const char *cp;
 	unsigned int pre_len, suf_len, slash_cnt = 0;
 
-	if (verbose > 2) {
+	if (DEBUG_GTE(FILTER, 2)) {
 		rprintf(FINFO, "[%s] add_rule(%s%.*s%s)%s\n",
-			who_am_i(), get_rule_prefix(mflags, pat, 0, NULL),
+			who_am_i(), get_rule_prefix(rule, pat, 0, NULL),
 			(int)pat_len, pat,
-			(mflags & MATCHFLG_DIRECTORY) ? "/" : "",
+			(rule->rflags & FILTRULE_DIRECTORY) ? "/" : "",
 			listp->debug_type);
 	}
 
 	/* These flags also indicate that we're reading a list that
 	 * needs to be filtered now, not post-filtered later. */
-	if (xflags & (XFLG_ANCHORED2ABS|XFLG_ABS_IF_SLASH)) {
-		uint32 mf = mflags & (MATCHFLG_RECEIVER_SIDE|MATCHFLG_SENDER_SIDE);
-		if (am_sender) {
-			if (mf == MATCHFLG_RECEIVER_SIDE)
-				return;
-		} else {
-			if (mf == MATCHFLG_SENDER_SIDE)
-				return;
-		}
+	if (xflags & (XFLG_ANCHORED2ABS|XFLG_ABS_IF_SLASH)
+		&& (rule->rflags & FILTRULES_SIDES)
+			== (am_sender ? FILTRULE_RECEIVER_SIDE : FILTRULE_SENDER_SIDE)) {
+		/* This filter applies only to the other side.  Drop it. */
+		free_filter(rule);
+		return;
 	}
 
-	if (!(ret = new0(struct filter_struct)))
-		out_of_memory("add_rule");
-
 	if (pat_len > 1 && pat[pat_len-1] == '/') {
 		pat_len--;
-		mflags |= MATCHFLG_DIRECTORY;
+		rule->rflags |= FILTRULE_DIRECTORY;
 	}
 
 	for (cp = pat; cp < pat + pat_len; cp++) {
 		if (*cp == '/')
 			slash_cnt++;
 	}
 
-	if (!(mflags & (MATCHFLG_ABS_PATH | MATCHFLG_MERGE_FILE))
+	if (!(rule->rflags & (FILTRULE_ABS_PATH | FILTRULE_MERGE_FILE))
 	 && ((xflags & (XFLG_ANCHORED2ABS|XFLG_ABS_IF_SLASH) && *pat == '/')
 	  || (xflags & XFLG_ABS_IF_SLASH && slash_cnt))) {
-		mflags |= MATCHFLG_ABS_PATH;
+		rule->rflags |= FILTRULE_ABS_PATH;
 		if (*pat == '/')
 			pre_len = dirbuf_len - module_dirlen - 1;
 		else
 			pre_len = 0;
 	} else
 		pre_len = 0;
 
 	/* The daemon wants dir-exclude rules to get an appended "/" + "***". */
 	if (xflags & XFLG_DIR2WILD3
-	 && BITS_SETnUNSET(mflags, MATCHFLG_DIRECTORY, MATCHFLG_INCLUDE)) {
-		mflags &= ~MATCHFLG_DIRECTORY;
+	 && BITS_SETnUNSET(rule->rflags, FILTRULE_DIRECTORY, FILTRULE_INCLUDE)) {
+		rule->rflags &= ~FILTRULE_DIRECTORY;
 		suf_len = sizeof SLASH_WILD3_SUFFIX - 1;
 	} else
 		suf_len = 0;
 
-	if (!(ret->pattern = new_array(char, pre_len + pat_len + suf_len + 1)))
+	if (!(rule->pattern = new_array(char, pre_len + pat_len + suf_len + 1)))
 		out_of_memory("add_rule");
 	if (pre_len) {
-		memcpy(ret->pattern, dirbuf + module_dirlen, pre_len);
-		for (cp = ret->pattern; cp < ret->pattern + pre_len; cp++) {
+		memcpy(rule->pattern, dirbuf + module_dirlen, pre_len);
+		for (cp = rule->pattern; cp < rule->pattern + pre_len; cp++) {
 			if (*cp == '/')
 				slash_cnt++;
 		}
 	}
-	strlcpy(ret->pattern + pre_len, pat, pat_len + 1);
+	strlcpy(rule->pattern + pre_len, pat, pat_len + 1);
 	pat_len += pre_len;
 	if (suf_len) {
-		memcpy(ret->pattern + pat_len, SLASH_WILD3_SUFFIX, suf_len+1);
+		memcpy(rule->pattern + pat_len, SLASH_WILD3_SUFFIX, suf_len+1);
 		pat_len += suf_len;
 		slash_cnt++;
 	}
 
-	if (strpbrk(ret->pattern, "*[?")) {
-		mflags |= MATCHFLG_WILD;
-		if ((cp = strstr(ret->pattern, "**")) != NULL) {
-			mflags |= MATCHFLG_WILD2;
+	if (strpbrk(rule->pattern, "*[?")) {
+		rule->rflags |= FILTRULE_WILD;
+		if ((cp = strstr(rule->pattern, "**")) != NULL) {
+			rule->rflags |= FILTRULE_WILD2;
 			/* If the pattern starts with **, note that. */
-			if (cp == ret->pattern)
-				mflags |= MATCHFLG_WILD2_PREFIX;
+			if (cp == rule->pattern)
+				rule->rflags |= FILTRULE_WILD2_PREFIX;
 			/* If the pattern ends with ***, note that. */
 			if (pat_len >= 3
-			 && ret->pattern[pat_len-3] == '*'
-			 && ret->pattern[pat_len-2] == '*'
-			 && ret->pattern[pat_len-1] == '*')
-				mflags |= MATCHFLG_WILD3_SUFFIX;
+			 && rule->pattern[pat_len-3] == '*'
+			 && rule->pattern[pat_len-2] == '*'
+			 && rule->pattern[pat_len-1] == '*')
+				rule->rflags |= FILTRULE_WILD3_SUFFIX;
 		}
 	}
 
-	if (mflags & MATCHFLG_PERDIR_MERGE) {
-		struct filter_list_struct *lp;
+	if (rule->rflags & FILTRULE_PERDIR_MERGE) {
+		filter_rule_list *lp;
 		unsigned int len;
 		int i;
 
-		if ((cp = strrchr(ret->pattern, '/')) != NULL)
+		if ((cp = strrchr(rule->pattern, '/')) != NULL)
 			cp++;
 		else
-			cp = ret->pattern;
+			cp = rule->pattern;
 
 		/* If the local merge file was already mentioned, don't
 		 * add it again. */
 		for (i = 0; i < mergelist_cnt; i++) {
-			struct filter_struct *ex = mergelist_parents[i];
+			filter_rule *ex = mergelist_parents[i];
 			const char *s = strrchr(ex->pattern, '/');
 			if (s)
 				s++;
 			else
 				s = ex->pattern;
 			len = strlen(s);
-			if (len == pat_len - (cp - ret->pattern)
-			    && memcmp(s, cp, len) == 0) {
-				free_filter(ret);
+			if (len == pat_len - (cp - rule->pattern) && memcmp(s, cp, len) == 0) {
+				free_filter(rule);
 				return;
 			}
 		}
 
-		if (!(lp = new_array(struct filter_list_struct, 1)))
+		if (!(lp = new_array(filter_rule_list, 1)))
 			out_of_memory("add_rule");
-		lp->head = lp->tail = NULL;
+		lp->head = lp->tail = lp->parent_dirscan_head = NULL;
 		if (asprintf(&lp->debug_type, " [per-dir %s]", cp) < 0)
 			out_of_memory("add_rule");
-		ret->u.mergelist = lp;
+		rule->u.mergelist = lp;
 
 		if (mergelist_cnt == mergelist_size) {
 			mergelist_size += 5;
 			mergelist_parents = realloc_array(mergelist_parents,
-						struct filter_struct *,
+						filter_rule *,
 						mergelist_size);
 			if (!mergelist_parents)
 				out_of_memory("add_rule");
 		}
-		mergelist_parents[mergelist_cnt++] = ret;
+		if (DEBUG_GTE(FILTER, 2)) {
+			rprintf(FINFO, "[%s] activating mergelist #%d%s\n",
+				who_am_i(), mergelist_cnt, lp->debug_type);
+		}
+		mergelist_parents[mergelist_cnt++] = rule;
 	} else
-		ret->u.slash_cnt = slash_cnt;
-
-	ret->match_flags = mflags;
+		rule->u.slash_cnt = slash_cnt;
 
 	if (!listp->tail) {
-		ret->next = listp->head;
-		listp->head = listp->tail = ret;
+		rule->next = listp->head;
+		listp->head = listp->tail = rule;
 	} else {
-		ret->next = listp->tail->next;
-		listp->tail->next = ret;
-		listp->tail = ret;
+		rule->next = listp->tail->next;
+		listp->tail->next = rule;
+		listp->tail = rule;
 	}
 }
 
-static void clear_filter_list(struct filter_list_struct *listp)
+static void clear_filter_list(filter_rule_list *listp)
 {
 	if (listp->tail) {
-		struct filter_struct *ent, *next;
 		/* Truncate any inherited items from the local list. */
 		listp->tail->next = NULL;
 		/* Now free everything that is left. */
-		for (ent = listp->head; ent; ent = next) {
-			next = ent->next;
-			free_filter(ent);
-		}
+		free_filters(listp->head);
 	}
 
 	listp->head = listp->tail = NULL;
 }
 
 /* This returns an expanded (absolute) filename for the merge-file name if
