static BOOL setup_merge_file(int mergelist_num, filter_rule *ex,
			     filter_rule_list *lp)
{
	char buf[MAXPATHLEN];
	char *x, *y, *pat = ex->pattern;
	unsigned int len;

	if (!(x = parse_merge_name(pat, NULL, 0)) || *x != '/')
		return 0;

	if (DEBUG_GTE(FILTER, 2)) {
		rprintf(FINFO, "[%s] performing parent_dirscan for mergelist #%d%s\n",
			who_am_i(), mergelist_num, lp->debug_type);
	}
	y = strrchr(x, '/');
	*y = '\0';
	ex->pattern = strdup(y+1);
	if (!*x)
		x = "/";
	if (*x == '/')
		strlcpy(buf, x, MAXPATHLEN);
	else
		pathjoin(buf, MAXPATHLEN, dirbuf, x);

	len = clean_fname(buf, CFN_COLLAPSE_DOT_DOT_DIRS);
	if (len != 1 && len < MAXPATHLEN-1) {
		buf[len++] = '/';
		buf[len] = '\0';
	}
	/* This ensures that the specified dir is a parent of the transfer. */
	for (x = buf, y = dirbuf; *x && *x == *y; x++, y++) {}
	if (*x)
		y += strlen(y); /* nope -- skip the scan */

	parent_dirscan = True;
	while (*y) {
		char save[MAXPATHLEN];
		strlcpy(save, y, MAXPATHLEN);
		*y = '\0';
		dirbuf_len = y - dirbuf;
		strlcpy(x, ex->pattern, MAXPATHLEN - (x - buf));
		parse_filter_file(lp, buf, ex, XFLG_ANCHORED2ABS);
		if (ex->rflags & FILTRULE_NO_INHERIT) {
			/* Free the undesired rules to clean up any per-dir
			 * mergelists they defined.  Otherwise pop_local_filters
			 * may crash trying to restore nonexistent state for
			 * those mergelists. */
			free_filters(lp->head);
			lp->head = NULL;
		}
		lp->tail = NULL;
		strlcpy(y, save, MAXPATHLEN);
		while ((*x++ = *y++) != '/') {}
	}
	parent_dirscan = False;
	if (DEBUG_GTE(FILTER, 2)) {
		rprintf(FINFO, "[%s] completed parent_dirscan for mergelist #%d%s\n",
			who_am_i(), mergelist_num, lp->debug_type);
	}
	free(pat);
	return 1;
}