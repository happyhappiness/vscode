static int reachable(struct commit *want)
{
	struct commit_list *work = NULL;

	commit_list_insert_by_date(want, &work);
	while (work) {
		struct commit_list *list;
		struct commit *commit = pop_commit(&work);

		if (commit->object.flags & THEY_HAVE) {
			want->object.flags |= COMMON_KNOWN;
			break;
		}
		if (!commit->object.parsed)
			parse_object(commit->object.oid.hash);
		if (commit->object.flags & REACHABLE)
			continue;
		commit->object.flags |= REACHABLE;
		if (commit->date < oldest_have)
			continue;
		for (list = commit->parents; list; list = list->next) {
			struct commit *parent = list->item;
			if (!(parent->object.flags & REACHABLE))
				commit_list_insert_by_date(parent, &work);
		}
	}
	want->object.flags |= REACHABLE;
	clear_commit_marks(want, REACHABLE);
	free_commit_list(work);
	return (want->object.flags & COMMON_KNOWN);
}