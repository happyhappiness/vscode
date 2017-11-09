static int reset_index(const struct object_id *oid, int reset_type, int quiet)
{
	int nr = 1;
	struct tree_desc desc[2];
	struct tree *tree;
	struct unpack_trees_options opts;

	memset(&opts, 0, sizeof(opts));
	opts.head_idx = 1;
	opts.src_index = &the_index;
	opts.dst_index = &the_index;
	opts.fn = oneway_merge;
	opts.merge = 1;
	if (!quiet)
		opts.verbose_update = 1;
	switch (reset_type) {
	case KEEP:
	case MERGE:
		opts.update = 1;
		break;
	case HARD:
		opts.update = 1;
		/* fallthrough */
	default:
		opts.reset = 1;
	}

	read_cache_unmerged();

	if (reset_type == KEEP) {
		struct object_id head_oid;
		if (get_oid("HEAD", &head_oid))
			return error(_("You do not have a valid HEAD."));
		if (!fill_tree_descriptor(desc, head_oid.hash))
			return error(_("Failed to find tree of HEAD."));
		nr++;
		opts.fn = twoway_merge;
	}

	if (!fill_tree_descriptor(desc + nr - 1, oid->hash))
		return error(_("Failed to find tree of %s."), oid_to_hex(oid));
	if (unpack_trees(nr, desc, &opts))
		return -1;

	if (reset_type == MIXED || reset_type == HARD) {
		tree = parse_tree_indirect(oid);
		prime_cache_tree(&the_index, tree);
	}

	return 0;
}