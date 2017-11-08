int sequencer_continue(struct replay_opts *opts)
{
	struct todo_list todo_list = TODO_LIST_INIT;
	int res;

	if (read_and_refresh_cache(opts))
		return -1;

	if (!file_exists(get_todo_path(opts)))
		return continue_single_pick();
	if (read_populate_opts(opts))
		return -1;
	if ((res = read_populate_todo(&todo_list, opts)))
		goto release_todo_list;

	/* Verify that the conflict has been resolved */
	if (file_exists(git_path_cherry_pick_head()) ||
	    file_exists(git_path_revert_head())) {
		res = continue_single_pick();
		if (res)
			goto release_todo_list;
	}
	if (index_differs_from("HEAD", 0, 0)) {
		res = error_dirty_index(opts);
		goto release_todo_list;
	}
	todo_list.current++;
	res = pick_commits(&todo_list, opts);
release_todo_list:
	todo_list_release(&todo_list);
	return res;
}