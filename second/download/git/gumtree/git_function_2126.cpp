static void combine_diff(const struct object_id *parent, unsigned int mode,
			 mmfile_t *result_file,
			 struct sline *sline, unsigned int cnt, int n,
			 int num_parent, int result_deleted,
			 struct userdiff_driver *textconv,
			 const char *path, long flags)
{
	unsigned int p_lno, lno;
	unsigned long nmask = (1UL << n);
	xpparam_t xpp;
	xdemitconf_t xecfg;
	mmfile_t parent_file;
	struct combine_diff_state state;
	unsigned long sz;

	if (result_deleted)
		return; /* result deleted */

	parent_file.ptr = grab_blob(parent, mode, &sz, textconv, path);
	parent_file.size = sz;
	memset(&xpp, 0, sizeof(xpp));
	xpp.flags = flags;
	memset(&xecfg, 0, sizeof(xecfg));
	memset(&state, 0, sizeof(state));
	state.nmask = nmask;
	state.sline = sline;
	state.lno = 1;
	state.num_parent = num_parent;
	state.n = n;

	if (xdi_diff_outf(&parent_file, result_file, consume_line, &state,
			  &xpp, &xecfg))
		die("unable to generate combined diff for %s",
		    oid_to_hex(parent));
	free(parent_file.ptr);

	/* Assign line numbers for this parent.
	 *
	 * sline[lno].p_lno[n] records the first line number
	 * (counting from 1) for parent N if the final hunk display
	 * started by showing sline[lno] (possibly showing the lost
	 * lines attached to it first).
	 */
	for (lno = 0,  p_lno = 1; lno <= cnt; lno++) {
		struct lline *ll;
		sline[lno].p_lno[n] = p_lno;

		/* Coalesce new lines */
		if (sline[lno].plost.lost_head) {
			struct sline *sl = &sline[lno];
			sl->lost = coalesce_lines(sl->lost, &sl->lenlost,
						  sl->plost.lost_head,
						  sl->plost.len, n, flags);
			sl->plost.lost_head = sl->plost.lost_tail = NULL;
			sl->plost.len = 0;
		}

		/* How many lines would this sline advance the p_lno? */
		ll = sline[lno].lost;
		while (ll) {
			if (ll->parent_map & nmask)
				p_lno++; /* '-' means parent had it */
			ll = ll->next;
		}
		if (lno < cnt && !(sline[lno].flag & nmask))
			p_lno++; /* no '+' means parent had it */
	}
	sline[lno].p_lno[n] = p_lno; /* trailer */
}