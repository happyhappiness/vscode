	opts.merge = 1;
	opts.fn = oneway_merge;
	opts.verbose_update = (option_verbosity >= 0);
	opts.src_index = &the_index;
	opts.dst_index = &the_index;

	tree = parse_tree_indirect(oid.hash);
	parse_tree(tree);
	init_tree_desc(&t, tree->buffer, tree->size);
	if (unpack_trees(1, &t, &opts) < 0)
		die(_("unable to checkout working tree"));

	if (write_locked_index(&the_index, lock_file, COMMIT_LOCK))
		die(_("unable to write new index file"));

	err |= run_hook_le(NULL, "post-checkout", sha1_to_hex(null_sha1),
			   oid_to_hex(&oid), "1", NULL);

	if (!err && (option_recurse_submodules.nr > 0)) {
		struct argv_array args = ARGV_ARRAY_INIT;
		argv_array_pushl(&args, "submodule", "update", "--init", "--recursive", NULL);

		if (option_shallow_submodules == 1)
			argv_array_push(&args, "--depth=1");

