	}

	return 0;
}

static int diff_cache(struct rev_info *revs,
		      const struct object_id *tree_oid,
		      const char *tree_name,
		      int cached)
{
	struct tree *tree;
	struct tree_desc t;
	struct unpack_trees_options opts;

	tree = parse_tree_indirect(tree_oid);
	if (!tree)
		return error("bad tree object %s",
			     tree_name ? tree_name : oid_to_hex(tree_oid));
	memset(&opts, 0, sizeof(opts));
	opts.head_idx = 1;
	opts.index_only = cached;
	opts.diff_index_cached = (cached &&
				  !DIFF_OPT_TST(&revs->diffopt, FIND_COPIES_HARDER));
	opts.merge = 1;
