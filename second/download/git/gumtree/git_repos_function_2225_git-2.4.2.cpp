static int sequencer_continue(struct replay_opts *opts)
{
	struct commit_list *todo_list = NULL;

	if (!file_exists(git_path(SEQ_TODO_FILE)))
		return continue_single_pick();
	read_populate_opts(&opts);
	read_populate_todo(&todo_list, opts);

	/* Verify that the conflict has been resolved */
	if (file_exists(git_path("CHERRY_PICK_HEAD")) ||
	    file_exists(git_path("REVERT_HEAD"))) {
		int ret = continue_single_pick();
		if (ret)
			return ret;
	}
	if (index_differs_from("HEAD", 0))
		return error_dirty_index(opts);
	todo_list = todo_list->next;
	return pick_commits(todo_list, opts);
}