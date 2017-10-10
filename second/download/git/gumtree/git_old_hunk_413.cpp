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

