static int run_apply(const struct am_state *state, const char *index_file)
{
	struct argv_array apply_paths = ARGV_ARRAY_INIT;
	struct argv_array apply_opts = ARGV_ARRAY_INIT;
	struct apply_state apply_state;
	int res, opts_left;
	static struct lock_file lock_file;
	int force_apply = 0;
	int options = 0;

	if (init_apply_state(&apply_state, NULL, &lock_file))
		die("BUG: init_apply_state() failed");

	argv_array_push(&apply_opts, "apply");
	argv_array_pushv(&apply_opts, state->git_apply_opts.argv);

	opts_left = apply_parse_options(apply_opts.argc, apply_opts.argv,
					&apply_state, &force_apply, &options,
					NULL);

	if (opts_left != 0)
		die("unknown option passed through to git apply");

	if (index_file) {
		apply_state.index_file = index_file;
		apply_state.cached = 1;
	} else
		apply_state.check_index = 1;

	/*
	 * If we are allowed to fall back on 3-way merge, don't give false
	 * errors during the initial attempt.
	 */
	if (state->threeway && !index_file)
		apply_state.apply_verbosity = verbosity_silent;

	if (check_apply_state(&apply_state, force_apply))
		die("BUG: check_apply_state() failed");

	argv_array_push(&apply_paths, am_path(state, "patch"));

	res = apply_all_patches(&apply_state, apply_paths.argc, apply_paths.argv, options);

	argv_array_clear(&apply_paths);
	argv_array_clear(&apply_opts);
	clear_apply_state(&apply_state);

	if (res)
		return res;

	if (index_file) {
		/* Reload index as apply_all_patches() will have modified it. */
		discard_cache();
		read_cache_from(index_file);
	}

	return 0;
}