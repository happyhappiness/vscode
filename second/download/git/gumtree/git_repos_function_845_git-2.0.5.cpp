static int mark_redundant_parents(struct rev_info *revs, struct commit *commit)
{
	struct commit_list *h = reduce_heads(commit->parents);
	int i = 0, marked = 0;
	struct commit_list *po, *pn;

	/* Want these for sanity-checking only */
	int orig_cnt = commit_list_count(commit->parents);
	int cnt = commit_list_count(h);

	/*
	 * Not ready to remove items yet, just mark them for now, based
	 * on the output of reduce_heads(). reduce_heads outputs the reduced
	 * set in its original order, so this isn't too hard.
	 */
	po = commit->parents;
	pn = h;
	while (po) {
		if (pn && po->item == pn->item) {
			pn = pn->next;
			i++;
		} else {
			po->item->object.flags |= TMP_MARK;
			marked++;
		}
		po=po->next;
	}

	if (i != cnt || cnt+marked != orig_cnt)
		die("mark_redundant_parents %d %d %d %d", orig_cnt, cnt, i, marked);

	free_commit_list(h);

	return marked;
}