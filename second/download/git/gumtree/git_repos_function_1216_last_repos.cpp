static struct commit *one_relevant_parent(const struct rev_info *revs,
					  struct commit_list *orig)
{
	struct commit_list *list = orig;
	struct commit *relevant = NULL;

	if (!orig)
		return NULL;

	/*
	 * For 1-parent commits, or if first-parent-only, then return that
	 * first parent (even if not "relevant" by the above definition).
	 * TREESAME will have been set purely on that parent.
	 */
	if (revs->first_parent_only || !orig->next)
		return orig->item;

	/*
	 * For multi-parent commits, identify a sole relevant parent, if any.
	 * If we have only one relevant parent, then TREESAME will be set purely
	 * with regard to that parent, and we can simplify accordingly.
	 *
	 * If we have more than one relevant parent, or no relevant parents
	 * (and multiple irrelevant ones), then we can't select a parent here
	 * and return NULL.
	 */
	while (list) {
		struct commit *commit = list->item;
		list = list->next;
		if (relevant_commit(commit)) {
			if (relevant)
				return NULL;
			relevant = commit;
		}
	}
	return relevant;
}