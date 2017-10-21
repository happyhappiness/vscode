 	while (*y) {
 		char save[MAXPATHLEN];
 		strlcpy(save, y, MAXPATHLEN);
 		*y = '\0';
 		dirbuf_len = y - dirbuf;
 		strlcpy(x, ex->pattern, MAXPATHLEN - (x - buf));
-		parse_filter_file(lp, buf, ex->match_flags, XFLG_ANCHORED2ABS);
-		if (ex->match_flags & MATCHFLG_NO_INHERIT)
+		parse_filter_file(lp, buf, ex, XFLG_ANCHORED2ABS);
+		if (ex->rflags & FILTRULE_NO_INHERIT) {
+			/* Free the undesired rules to clean up any per-dir
+			 * mergelists they defined.  Otherwise pop_local_filters
+			 * may crash trying to restore nonexistent state for
+			 * those mergelists. */
+			free_filters(lp->head);
 			lp->head = NULL;
+		}
 		lp->tail = NULL;
 		strlcpy(y, save, MAXPATHLEN);
 		while ((*x++ = *y++) != '/') {}
 	}
+	/* Save current head for freeing when the mergelist becomes inactive. */
+	lp->parent_dirscan_head = lp->head;
 	parent_dirscan = False;
+	if (DEBUG_GTE(FILTER, 2)) {
+		rprintf(FINFO, "[%s] completed parent_dirscan for mergelist #%d%s\n",
+			who_am_i(), mergelist_num, lp->debug_type);
+	}
 	free(pat);
 	return 1;
 }
 
+struct local_filter_state {
+	int mergelist_cnt;
+	filter_rule_list mergelists[1];
+};
+
 /* Each time rsync changes to a new directory it call this function to
  * handle all the per-dir merge-files.  The "dir" value is the current path
  * relative to curr_dir (which might not be null-terminated).  We copy it
  * into dirbuf so that we can easily append a file name on the end. */
 void *push_local_filters(const char *dir, unsigned int dirlen)
 {
-	struct filter_list_struct *ap, *push;
+	struct local_filter_state *push;
 	int i;
 
 	set_filter_dir(dir, dirlen);
+	if (DEBUG_GTE(FILTER, 2)) {
+		rprintf(FINFO, "[%s] pushing local filters for %s\n",
+			who_am_i(), dirbuf);
+	}
 
-	if (!mergelist_cnt)
+	if (!mergelist_cnt) {
+		/* No old state to save and no new merge files to push. */
 		return NULL;
+	}
 
-	push = new_array(struct filter_list_struct, mergelist_cnt);
+	push = (struct local_filter_state *)new_array(char,
+			  sizeof (struct local_filter_state)
+			+ (mergelist_cnt-1) * sizeof (filter_rule_list));
 	if (!push)
 		out_of_memory("push_local_filters");
 
-	for (i = 0, ap = push; i < mergelist_cnt; i++) {
-		memcpy(ap++, mergelist_parents[i]->u.mergelist,
-		       sizeof (struct filter_list_struct));
+	push->mergelist_cnt = mergelist_cnt;
+	for (i = 0; i < mergelist_cnt; i++) {
+		memcpy(&push->mergelists[i], mergelist_parents[i]->u.mergelist,
+		       sizeof (filter_rule_list));
 	}
 
 	/* Note: parse_filter_file() might increase mergelist_cnt, so keep
 	 * this loop separate from the above loop. */
 	for (i = 0; i < mergelist_cnt; i++) {
-		struct filter_struct *ex = mergelist_parents[i];
-		struct filter_list_struct *lp = ex->u.mergelist;
+		filter_rule *ex = mergelist_parents[i];
+		filter_rule_list *lp = ex->u.mergelist;
 
-		if (verbose > 2) {
-			rprintf(FINFO, "[%s] pushing filter list%s\n",
-				who_am_i(), lp->debug_type);
+		if (DEBUG_GTE(FILTER, 2)) {
+			rprintf(FINFO, "[%s] pushing mergelist #%d%s\n",
+				who_am_i(), i, lp->debug_type);
 		}
 
 		lp->tail = NULL; /* Switch any local rules to inherited. */
-		if (ex->match_flags & MATCHFLG_NO_INHERIT)
+		if (ex->rflags & FILTRULE_NO_INHERIT)
 			lp->head = NULL;
 
-		if (ex->match_flags & MATCHFLG_FINISH_SETUP) {
-			ex->match_flags &= ~MATCHFLG_FINISH_SETUP;
-			if (setup_merge_file(ex, lp))
+		if (ex->rflags & FILTRULE_FINISH_SETUP) {
+			ex->rflags &= ~FILTRULE_FINISH_SETUP;
+			if (setup_merge_file(i, ex, lp))
 				set_filter_dir(dir, dirlen);
 		}
 
 		if (strlcpy(dirbuf + dirbuf_len, ex->pattern,
 		    MAXPATHLEN - dirbuf_len) < MAXPATHLEN - dirbuf_len) {
-			parse_filter_file(lp, dirbuf, ex->match_flags,
+			parse_filter_file(lp, dirbuf, ex,
 					  XFLG_ANCHORED2ABS);
 		} else {
 			io_error |= IOERR_GENERAL;
 			rprintf(FERROR,
 			    "cannot add local filter rules in long-named directory: %s\n",
 			    full_fname(dirbuf));
