static void walk_revs_populate_todo(struct commit_list **todo_list,
				struct replay_opts *opts)
{
	struct commit *commit;
	struct commit_list **next;

	prepare_revs(opts);

	next = todo_list;
	while ((commit = get_revision(opts->revs)))
		next = commit_list_append(commit, next);
}