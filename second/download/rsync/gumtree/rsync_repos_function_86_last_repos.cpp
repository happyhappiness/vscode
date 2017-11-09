void *push_local_filters(const char *dir, unsigned int dirlen)
{
	struct local_filter_state *push;
	int i;

	set_filter_dir(dir, dirlen);
	if (DEBUG_GTE(FILTER, 2)) {
		rprintf(FINFO, "[%s] pushing local filters for %s\n",
			who_am_i(), dirbuf);
	}

	if (!mergelist_cnt) {
		/* No old state to save and no new merge files to push. */
		return NULL;
	}

	push = (struct local_filter_state *)new_array(char,
			  sizeof (struct local_filter_state)
			+ (mergelist_cnt-1) * sizeof (filter_rule_list));
	if (!push)
		out_of_memory("push_local_filters");

	push->mergelist_cnt = mergelist_cnt;
	for (i = 0; i < mergelist_cnt; i++) {
		filter_rule *ex = mergelist_parents[i];
		if (!ex)
			continue;
		memcpy(&push->mergelists[i], ex->u.mergelist, sizeof (filter_rule_list));
	}

	/* Note: parse_filter_file() might increase mergelist_cnt, so keep
	 * this loop separate from the above loop. */
	for (i = 0; i < mergelist_cnt; i++) {
		filter_rule *ex = mergelist_parents[i];
		filter_rule_list *lp;
		if (!ex)
			continue;
		lp = ex->u.mergelist;

		if (DEBUG_GTE(FILTER, 2)) {
			rprintf(FINFO, "[%s] pushing mergelist #%d%s\n",
				who_am_i(), i, lp->debug_type);
		}

		lp->tail = NULL; /* Switch any local rules to inherited. */
		if (ex->rflags & FILTRULE_NO_INHERIT)
			lp->head = NULL;

		if (ex->rflags & FILTRULE_FINISH_SETUP) {
			ex->rflags &= ~FILTRULE_FINISH_SETUP;
			if (setup_merge_file(i, ex, lp))
				set_filter_dir(dir, dirlen);
		}

		if (strlcpy(dirbuf + dirbuf_len, ex->pattern,
		    MAXPATHLEN - dirbuf_len) < MAXPATHLEN - dirbuf_len) {
			parse_filter_file(lp, dirbuf, ex,
					  XFLG_ANCHORED2ABS);
		} else {
			io_error |= IOERR_GENERAL;
			rprintf(FERROR,
			    "cannot add local filter rules in long-named directory: %s\n",
			    full_fname(dirbuf));
		}
		dirbuf[dirbuf_len] = '\0';
	}

	return (void*)push;
}