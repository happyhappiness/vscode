int prepare_revision_walk(struct rev_info *revs)
{
	int i;
	struct object_array old_pending;
	struct commit_list **next = &revs->commits;

	memcpy(&old_pending, &revs->pending, sizeof(old_pending));
	revs->pending.nr = 0;
	revs->pending.alloc = 0;
	revs->pending.objects = NULL;
	for (i = 0; i < old_pending.nr; i++) {
		struct object_array_entry *e = old_pending.objects + i;
		struct commit *commit = handle_commit(revs, e);
		if (commit) {
			if (!(commit->object.flags & SEEN)) {
				commit->object.flags |= SEEN;
				next = commit_list_append(commit, next);
			}
		}
	}
	if (!revs->leak_pending)
		object_array_clear(&old_pending);

	/* Signal whether we need per-parent treesame decoration */
	if (revs->simplify_merges ||
	    (revs->limited && limiting_can_increase_treesame(revs)))
		revs->treesame.name = "treesame";

	if (revs->no_walk != REVISION_WALK_NO_WALK_UNSORTED)
		commit_list_sort_by_date(&revs->commits);
	if (revs->no_walk)
		return 0;
	if (revs->limited)
		if (limit_list(revs) < 0)
			return -1;
	if (revs->topo_order)
		sort_in_topological_order(&revs->commits, revs->sort_order);
	if (revs->line_level_traverse)
		line_log_filter(revs);
	if (revs->simplify_merges)
		simplify_merges(revs);
	if (revs->children.name)
		set_children(revs);
	return 0;
}