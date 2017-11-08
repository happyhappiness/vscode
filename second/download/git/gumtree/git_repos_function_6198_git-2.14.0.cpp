static int read_tree_trivial(struct object_id *common, struct object_id *head,
			     struct object_id *one)
{
	int i, nr_trees = 0;
	struct tree *trees[MAX_UNPACK_TREES];
	struct tree_desc t[MAX_UNPACK_TREES];
	struct unpack_trees_options opts;

	memset(&opts, 0, sizeof(opts));
	opts.head_idx = 2;
	opts.src_index = &the_index;
	opts.dst_index = &the_index;
	opts.update = 1;
	opts.verbose_update = 1;
	opts.trivial_merges_only = 1;
	opts.merge = 1;
	trees[nr_trees] = parse_tree_indirect(common);
	if (!trees[nr_trees++])
		return -1;
	trees[nr_trees] = parse_tree_indirect(head);
	if (!trees[nr_trees++])
		return -1;
	trees[nr_trees] = parse_tree_indirect(one);
	if (!trees[nr_trees++])
		return -1;
	opts.fn = threeway_merge;
	cache_tree_free(&active_cache_tree);
	for (i = 0; i < nr_trees; i++) {
		parse_tree(trees[i]);
		init_tree_desc(t+i, trees[i]->buffer, trees[i]->size);
	}
	if (unpack_trees(nr_trees, t, &opts))
		return -1;
	return 0;
}