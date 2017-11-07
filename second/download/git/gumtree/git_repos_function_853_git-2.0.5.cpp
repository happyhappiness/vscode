int prepare_revision_walk(struct rev_info *revs)
{
	int nr = revs->pending.nr;
	struct object_array_entry *e, *list;
	struct commit_list **next = &revs->commits;

	e = list = revs->pending.objects;
	revs->pending.nr = 0;
	revs->pending.alloc = 0;
	revs->pending.objects = NULL;
	while (--nr >= 0) {
		struct commit *commit = handle_commit(revs, e->item, e->name);
		if (commit) {
			if (!(commit->object.flags & SEEN)) {
				commit->object.flags |= SEEN;
				next = commit_list_append(commit, next);
			}
		}
		e++;
	}
	if (!revs->leak_pending)
		free(list);

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