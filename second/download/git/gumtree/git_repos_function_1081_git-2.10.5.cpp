static struct commit_list **simplify_one(struct rev_info *revs, struct commit *commit, struct commit_list **tail)
{
	struct commit_list *p;
	struct commit *parent;
	struct merge_simplify_state *st, *pst;
	int cnt;

	st = locate_simplify_state(revs, commit);

	/*
	 * Have we handled this one?
	 */
	if (st->simplified)
		return tail;

	/*
	 * An UNINTERESTING commit simplifies to itself, so does a
	 * root commit.  We do not rewrite parents of such commit
	 * anyway.
	 */
	if ((commit->object.flags & UNINTERESTING) || !commit->parents) {
		st->simplified = commit;
		return tail;
	}

	/*
	 * Do we know what commit all of our parents that matter
	 * should be rewritten to?  Otherwise we are not ready to
	 * rewrite this one yet.
	 */
	for (cnt = 0, p = commit->parents; p; p = p->next) {
		pst = locate_simplify_state(revs, p->item);
		if (!pst->simplified) {
			tail = &commit_list_insert(p->item, tail)->next;
			cnt++;
		}
		if (revs->first_parent_only)
			break;
	}
	if (cnt) {
		tail = &commit_list_insert(commit, tail)->next;
		return tail;
	}

	/*
	 * Rewrite our list of parents. Note that this cannot
	 * affect our TREESAME flags in any way - a commit is
	 * always TREESAME to its simplification.
	 */
	for (p = commit->parents; p; p = p->next) {
		pst = locate_simplify_state(revs, p->item);
		p->item = pst->simplified;
		if (revs->first_parent_only)
			break;
	}

	if (revs->first_parent_only)
		cnt = 1;
	else
		cnt = remove_duplicate_parents(revs, commit);

	/*
	 * It is possible that we are a merge and one side branch
	 * does not have any commit that touches the given paths;
	 * in such a case, the immediate parent from that branch
	 * will be rewritten to be the merge base.
	 *
	 *      o----X		X: the commit we are looking at;
	 *     /    /		o: a commit that touches the paths;
	 * ---o----'
	 *
	 * Further, a merge of an independent branch that doesn't
	 * touch the path will reduce to a treesame root parent:
	 *
	 *  ----o----X		X: the commit we are looking at;
	 *          /		o: a commit that touches the paths;
	 *         r		r: a root commit not touching the paths
	 *
	 * Detect and simplify both cases.
	 */
	if (1 < cnt) {
		int marked = mark_redundant_parents(revs, commit);
		marked += mark_treesame_root_parents(revs, commit);
		if (marked)
			marked -= leave_one_treesame_to_parent(revs, commit);
		if (marked)
			cnt = remove_marked_parents(revs, commit);
	}

	/*
	 * A commit simplifies to itself if it is a root, if it is
	 * UNINTERESTING, if it touches the given paths, or if it is a
	 * merge and its parents don't simplify to one relevant commit
	 * (the first two cases are already handled at the beginning of
	 * this function).
	 *
	 * Otherwise, it simplifies to what its sole relevant parent
	 * simplifies to.
	 */
	if (!cnt ||
	    (commit->object.flags & UNINTERESTING) ||
	    !(commit->object.flags & TREESAME) ||
	    (parent = one_relevant_parent(revs, commit->parents)) == NULL)
		st->simplified = commit;
	else {
		pst = locate_simplify_state(revs, parent);
		st->simplified = pst->simplified;
	}
	return tail;
}