static struct commit_list *collect_parents(struct commit *head_commit,
					   int *head_subsumed,
					   int argc, const char **argv,
					   struct strbuf *merge_msg)
{
	int i;
	struct commit_list *remoteheads = NULL;
	struct commit_list **remotes = &remoteheads;
	struct strbuf merge_names = STRBUF_INIT, *autogen = NULL;

	if (merge_msg && (!have_message || shortlog_len))
		autogen = &merge_names;

	if (head_commit)
		remotes = &commit_list_insert(head_commit, remotes)->next;

	if (argc == 1 && !strcmp(argv[0], "FETCH_HEAD")) {
		handle_fetch_head(remotes, autogen);
		remoteheads = reduce_parents(head_commit, head_subsumed, remoteheads);
	} else {
		for (i = 0; i < argc; i++) {
			struct commit *commit = get_merge_parent(argv[i]);
			if (!commit)
				help_unknown_ref(argv[i], "merge",
						 "not something we can merge");
			remotes = &commit_list_insert(commit, remotes)->next;
		}
		remoteheads = reduce_parents(head_commit, head_subsumed, remoteheads);
		if (autogen) {
			struct commit_list *p;
			for (p = remoteheads; p; p = p->next)
				merge_name(merge_remote_util(p->item)->name, autogen);
		}
	}

	if (autogen) {
		prepare_merge_message(autogen, merge_msg);
		strbuf_release(autogen);
	}

	return remoteheads;
}