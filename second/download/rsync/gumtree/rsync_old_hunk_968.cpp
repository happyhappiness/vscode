	while (*y) {
		char save[MAXPATHLEN];
		strlcpy(save, y, MAXPATHLEN);
		*y = '\0';
		dirbuf_len = y - dirbuf;
		strlcpy(x, ex->pattern, MAXPATHLEN - (x - buf));
		parse_filter_file(lp, buf, ex->match_flags, XFLG_ANCHORED2ABS);
		if (ex->match_flags & MATCHFLG_NO_INHERIT)
			lp->head = NULL;
		lp->tail = NULL;
		strlcpy(y, save, MAXPATHLEN);
		while ((*x++ = *y++) != '/') {}
	}
	parent_dirscan = False;
	free(pat);
	return 1;
}

/* Each time rsync changes to a new directory it call this function to
 * handle all the per-dir merge-files.  The "dir" value is the current path
 * relative to curr_dir (which might not be null-terminated).  We copy it
 * into dirbuf so that we can easily append a file name on the end. */
void *push_local_filters(const char *dir, unsigned int dirlen)
{
	struct filter_list_struct *ap, *push;
	int i;

	set_filter_dir(dir, dirlen);

	if (!mergelist_cnt)
		return NULL;

	push = new_array(struct filter_list_struct, mergelist_cnt);
	if (!push)
		out_of_memory("push_local_filters");

	for (i = 0, ap = push; i < mergelist_cnt; i++) {
		memcpy(ap++, mergelist_parents[i]->u.mergelist,
		       sizeof (struct filter_list_struct));
	}

	/* Note: parse_filter_file() might increase mergelist_cnt, so keep
	 * this loop separate from the above loop. */
	for (i = 0; i < mergelist_cnt; i++) {
		struct filter_struct *ex = mergelist_parents[i];
		struct filter_list_struct *lp = ex->u.mergelist;

		if (verbose > 2) {
			rprintf(FINFO, "[%s] pushing filter list%s\n",
				who_am_i(), lp->debug_type);
		}

		lp->tail = NULL; /* Switch any local rules to inherited. */
		if (ex->match_flags & MATCHFLG_NO_INHERIT)
			lp->head = NULL;

		if (ex->match_flags & MATCHFLG_FINISH_SETUP) {
			ex->match_flags &= ~MATCHFLG_FINISH_SETUP;
			if (setup_merge_file(ex, lp))
				set_filter_dir(dir, dirlen);
		}

		if (strlcpy(dirbuf + dirbuf_len, ex->pattern,
		    MAXPATHLEN - dirbuf_len) < MAXPATHLEN - dirbuf_len) {
			parse_filter_file(lp, dirbuf, ex->match_flags,
					  XFLG_ANCHORED2ABS);
		} else {
			io_error |= IOERR_GENERAL;
			rprintf(FERROR,
			    "cannot add local filter rules in long-named directory: %s\n",
			    full_fname(dirbuf));
