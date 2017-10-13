static int reset_index(const unsigned char *sha1, int reset_type, int quiet)
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
		unsigned char head_sha1[20];
		if (get_sha1("HEAD", head_sha1))
			return error(_("You do not have a valid HEAD."));
		if (!fill_tree_descriptor(desc, head_sha1))
			return error(_("Failed to find tree of HEAD."));
		nr++;
		opts.fn = twoway_merge;
	}

	if (!fill_tree_descriptor(desc + nr - 1, sha1))
		return error(_("Failed to find tree of %s."), sha1_to_hex(sha1));
	if (unpack_trees(nr, desc, &opts))
		return -1;

	if (reset_type == MIXED || reset_type == HARD) {
		tree = parse_tree_indirect(sha1);
		prime_cache_tree(&the_index, tree);
	}

	return 0;
}