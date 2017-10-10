		die("unpack_trees takes at most %d trees", MAX_UNPACK_TREES);
	memset(&state, 0, sizeof(state));
	state.base_dir = "";
	state.force = 1;
	state.quiet = 1;
	state.refresh_cache = 1;

	memset(&el, 0, sizeof(el));
	if (!core_apply_sparse_checkout || !o->update)
		o->skip_sparse_checkout = 1;
	if (!o->skip_sparse_checkout) {
		if (add_excludes_from_file_to_list(git_path("info/sparse-checkout"), "", 0, &el, 0) < 0)
