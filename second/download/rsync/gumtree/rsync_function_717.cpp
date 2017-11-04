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
			rprintf(FINFO,
			    "cannot add local filter rules in long-named directory: %s\n",
			    full_fname(dirbuf));
		}
		dirbuf[dirbuf_len] = '\0';
	}

	return (void*)push;
}