static void mark_reachable(struct expire_reflog_policy_cb *cb)
{
	struct commit_list *pending;
	timestamp_t expire_limit = cb->mark_limit;
	struct commit_list *leftover = NULL;

	for (pending = cb->mark_list; pending; pending = pending->next)
		pending->item->object.flags &= ~REACHABLE;

	pending = cb->mark_list;
	while (pending) {
		struct commit_list *parent;
		struct commit *commit = pop_commit(&pending);
		if (commit->object.flags & REACHABLE)
			continue;
		if (parse_commit(commit))
			continue;
		commit->object.flags |= REACHABLE;
		if (commit->date < expire_limit) {
			commit_list_insert(commit, &leftover);
			continue;
		}
		commit->object.flags |= REACHABLE;
		parent = commit->parents;
		while (parent) {
			commit = parent->item;
			parent = parent->next;
			if (commit->object.flags & REACHABLE)
				continue;
			commit_list_insert(commit, &pending);
		}
	}
	cb->mark_list = leftover;
}