static int reachable(struct commit *want)
{
	struct prio_queue work = { compare_commits_by_commit_date };

	prio_queue_put(&work, want);
	while (work.nr) {
		struct commit_list *list;
		struct commit *commit = prio_queue_get(&work);

		if (commit->object.flags & THEY_HAVE) {
			want->object.flags |= COMMON_KNOWN;
			break;
		}
		if (!commit->object.parsed)
			parse_object(&commit->object.oid);
		if (commit->object.flags & REACHABLE)
			continue;
		commit->object.flags |= REACHABLE;
		if (commit->date < oldest_have)
			continue;
		for (list = commit->parents; list; list = list->next) {
			struct commit *parent = list->item;
			if (!(parent->object.flags & REACHABLE))
				prio_queue_put(&work, parent);
		}
	}
	want->object.flags |= REACHABLE;
	clear_commit_marks(want, REACHABLE);
	clear_prio_queue(&work);
	return (want->object.flags & COMMON_KNOWN);
}