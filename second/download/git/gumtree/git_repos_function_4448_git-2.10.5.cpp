static void blame_chunk(struct blame_entry ***dstq, struct blame_entry ***srcq,
			int tlno, int offset, int same,
			struct origin *parent)
{
	struct blame_entry *e = **srcq;
	struct blame_entry *samep = NULL, *diffp = NULL;

	while (e && e->s_lno < tlno) {
		struct blame_entry *next = e->next;
		/*
		 * current record starts before differing portion.  If
		 * it reaches into it, we need to split it up and
		 * examine the second part separately.
		 */
		if (e->s_lno + e->num_lines > tlno) {
			/* Move second half to a new record */
			int len = tlno - e->s_lno;
			struct blame_entry *n = xcalloc(1, sizeof (struct blame_entry));
			n->suspect = e->suspect;
			n->lno = e->lno + len;
			n->s_lno = e->s_lno + len;
			n->num_lines = e->num_lines - len;
			e->num_lines = len;
			e->score = 0;
			/* Push new record to diffp */
			n->next = diffp;
			diffp = n;
		} else
			origin_decref(e->suspect);
		/* Pass blame for everything before the differing
		 * chunk to the parent */
		e->suspect = origin_incref(parent);
		e->s_lno += offset;
		e->next = samep;
		samep = e;
		e = next;
	}
	/*
	 * As we don't know how much of a common stretch after this
	 * diff will occur, the currently blamed parts are all that we
	 * can assign to the parent for now.
	 */

	if (samep) {
		**dstq = reverse_blame(samep, **dstq);
		*dstq = &samep->next;
	}
	/*
	 * Prepend the split off portions: everything after e starts
	 * after the blameable portion.
	 */
	e = reverse_blame(diffp, e);

	/*
	 * Now retain records on the target while parts are different
	 * from the parent.
	 */
	samep = NULL;
	diffp = NULL;
	while (e && e->s_lno < same) {
		struct blame_entry *next = e->next;

		/*
		 * If current record extends into sameness, need to split.
		 */
		if (e->s_lno + e->num_lines > same) {
			/*
			 * Move second half to a new record to be
			 * processed by later chunks
			 */
			int len = same - e->s_lno;
			struct blame_entry *n = xcalloc(1, sizeof (struct blame_entry));
			n->suspect = origin_incref(e->suspect);
			n->lno = e->lno + len;
			n->s_lno = e->s_lno + len;
			n->num_lines = e->num_lines - len;
			e->num_lines = len;
			e->score = 0;
			/* Push new record to samep */
			n->next = samep;
			samep = n;
		}
		e->next = diffp;
		diffp = e;
		e = next;
	}
	**srcq = reverse_blame(diffp, reverse_blame(samep, e));
	/* Move across elements that are in the unblamable portion */
	if (diffp)
		*srcq = &diffp->next;
}