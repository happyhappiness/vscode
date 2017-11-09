static int remove_duplicate_parents(struct rev_info *revs, struct commit *commit)
{
	struct treesame_state *ts = lookup_decoration(&revs->treesame, &commit->object);
	struct commit_list **pp, *p;
	int surviving_parents;

	/* Examine existing parents while marking ones we have seen... */
	pp = &commit->parents;
	surviving_parents = 0;
	while ((p = *pp) != NULL) {
		struct commit *parent = p->item;
		if (parent->object.flags & TMP_MARK) {
			*pp = p->next;
			if (ts)
				compact_treesame(revs, commit, surviving_parents);
			continue;
		}
		parent->object.flags |= TMP_MARK;
		surviving_parents++;
		pp = &p->next;
	}
	/* clear the temporary mark */
	for (p = commit->parents; p; p = p->next) {
		p->item->object.flags &= ~TMP_MARK;
	}
	/* no update_treesame() - removing duplicates can't affect TREESAME */
	return surviving_parents;
}