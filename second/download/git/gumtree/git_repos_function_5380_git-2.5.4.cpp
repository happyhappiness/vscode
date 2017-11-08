static struct commit_list *reduce_parents(struct commit *head_commit,
					  int *head_subsumed,
					  struct commit_list *remoteheads)
{
	struct commit_list *parents, *next, **remotes = &remoteheads;

	/*
	 * Is the current HEAD reachable from another commit being
	 * merged?  If so we do not want to record it as a parent of
	 * the resulting merge, unless --no-ff is given.  We will flip
	 * this variable to 0 when we find HEAD among the independent
	 * tips being merged.
	 */
	*head_subsumed = 1;

	/* Find what parents to record by checking independent ones. */
	parents = reduce_heads(remoteheads);

	for (remoteheads = NULL, remotes = &remoteheads;
	     parents;
	     parents = next) {
		struct commit *commit = parents->item;
		next = parents->next;
		if (commit == head_commit)
			*head_subsumed = 0;
		else
			remotes = &commit_list_insert(commit, remotes)->next;
		free(parents);
	}
	return remoteheads;
}