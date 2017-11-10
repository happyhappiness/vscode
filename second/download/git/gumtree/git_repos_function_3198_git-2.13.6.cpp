int line_log_filter(struct rev_info *rev)
{
	struct commit *commit;
	struct commit_list *list = rev->commits;
	struct commit_list *out = NULL, **pp = &out;

	while (list) {
		struct commit_list *to_free = NULL;
		commit = list->item;
		if (process_ranges_arbitrary_commit(rev, commit)) {
			*pp = list;
			pp = &list->next;
		} else
			to_free = list;
		list = list->next;
		free(to_free);
	}
	*pp = NULL;

	for (list = out; list; list = list->next)
		rewrite_parents(rev, list->item, line_log_rewrite_one);

	rev->commits = out;

	return 0;
}