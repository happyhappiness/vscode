	if ((!revs.commits &&
	     (!(revs.tag_objects || revs.tree_objects || revs.blob_objects) &&
	      !revs.pending.nr)) ||
	    revs.diff)
		usage(rev_list_usage);

	save_commit_buffer = (revs.verbose_header ||
			      revs.grep_filter.pattern_list ||
			      revs.grep_filter.header_list);
	if (bisect_list)
		revs.limited = 1;

