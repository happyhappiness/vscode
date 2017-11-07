static int diff_cache(struct rev_info *revs,
		      const unsigned char *tree_sha1,
		      const char *tree_name,
		      int cached)
{
	struct tree *tree;
	struct tree_desc t;
	struct unpack_trees_options opts;

	tree = parse_tree_indirect(tree_sha1);
	if (!tree)
		return error("bad tree object %s",
			     tree_name ? tree_name : sha1_to_hex(tree_sha1));
	memset(&opts, 0, sizeof(opts));
	opts.head_idx = 1;
	opts.index_only = cached;
	opts.diff_index_cached = (cached &&
				  !DIFF_OPT_TST(&revs->diffopt, FIND_COPIES_HARDER));
	opts.merge = 1;
	opts.fn = oneway_diff;
	opts.unpack_data = revs;
	opts.src_index = &the_index;
	opts.dst_index = NULL;
	opts.pathspec = &revs->diffopt.pathspec;
	opts.pathspec->recursive = 1;

	init_tree_desc(&t, tree->buffer, tree->size);
	return unpack_trees(1, &t, &opts);
}