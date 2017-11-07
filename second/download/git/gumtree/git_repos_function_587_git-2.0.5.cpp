static struct commit_list *paint_down_to_common(struct commit *one, int n, struct commit **twos)
{
	struct commit_list *list = NULL;
	struct commit_list *result = NULL;
	int i;

	one->object.flags |= PARENT1;
	commit_list_insert_by_date(one, &list);
	if (!n)
		return list;
	for (i = 0; i < n; i++) {
		twos[i]->object.flags |= PARENT2;
		commit_list_insert_by_date(twos[i], &list);
	}

	while (interesting(list)) {
		struct commit *commit;
		struct commit_list *parents;
		struct commit_list *next;
		int flags;

		commit = list->item;
		next = list->next;
		free(list);
		list = next;

		flags = commit->object.flags & (PARENT1 | PARENT2 | STALE);
		if (flags == (PARENT1 | PARENT2)) {
			if (!(commit->object.flags & RESULT)) {
				commit->object.flags |= RESULT;
				commit_list_insert_by_date(commit, &result);
			}
			/* Mark parents of a found merge stale */
			flags |= STALE;
		}
		parents = commit->parents;
		while (parents) {
			struct commit *p = parents->item;
			parents = parents->next;
			if ((p->object.flags & flags) == flags)
				continue;
			if (parse_commit(p))
				return NULL;
			p->object.flags |= flags;
			commit_list_insert_by_date(p, &list);
		}
	}

	free_commit_list(list);
	return result;
}