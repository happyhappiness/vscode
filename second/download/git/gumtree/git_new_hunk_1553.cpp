	 * progress
	 */

	if (walk_revs_populate_todo(&todo_list, opts) ||
			create_seq_dir() < 0)
		return -1;
	if (get_oid("HEAD", &oid) && (opts->action == REPLAY_REVERT))
		return error(_("can't revert as initial commit"));
	if (save_head(oid_to_hex(&oid)))
		return -1;
	if (save_opts(opts))
		return -1;
	update_abort_safety_file();
	res = pick_commits(&todo_list, opts);
	todo_list_release(&todo_list);
