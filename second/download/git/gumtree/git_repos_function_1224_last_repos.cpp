static inline int limiting_can_increase_treesame(const struct rev_info *revs)
{
	/*
	 * TREESAME is irrelevant unless prune && dense;
	 * if simplify_history is set, we can't have a mixture of TREESAME and
	 *    !TREESAME INTERESTING parents (and we don't have treesame[]
	 *    decoration anyway);
	 * if first_parent_only is set, then the TREESAME flag is locked
	 *    against the first parent (and again we lack treesame[] decoration).
	 */
	return revs->prune && revs->dense &&
	       !revs->simplify_history &&
	       !revs->first_parent_only;
}