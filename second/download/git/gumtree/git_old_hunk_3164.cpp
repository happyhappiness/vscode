		return merge_abort(&o);
	if (do_commit)
		return merge_commit(&o);

	o.local_ref = default_notes_ref();
	strbuf_addstr(&remote_ref, argv[0]);
	expand_notes_ref(&remote_ref);
	o.remote_ref = remote_ref.buf;

	t = init_notes_check("merge");

	if (strategy) {
		if (parse_notes_merge_strategy(strategy, &o.strategy)) {
			error("Unknown -s/--strategy: %s", strategy);
			usage_with_options(git_notes_merge_usage, options);
		}
