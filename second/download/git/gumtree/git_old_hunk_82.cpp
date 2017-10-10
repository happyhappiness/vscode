	tree = parse_tree_indirect(sha1);
	parse_tree(tree);
	init_tree_desc(&t, tree->buffer, tree->size);
	if (unpack_trees(1, &t, &opts) < 0)
		die(_("unable to checkout working tree"));

	if (write_cache(fd, active_cache, active_nr) ||
	    commit_locked_index(lock_file))
		die(_("unable to write new index file"));

	err |= run_hook_le(NULL, "post-checkout", sha1_to_hex(null_sha1),
			   sha1_to_hex(sha1), "1", NULL);

	if (!err && option_recursive)
