	save_commit_buffer = (revs.verbose_header ||
			      revs.grep_filter.pattern_list ||
			      revs.grep_filter.header_list);
	if (bisect_list)
		revs.limited = 1;

	if (use_bitmap_index) {
		if (revs.count && !revs.left_right && !revs.cherry_mark) {
			uint32_t commit_count;
			if (!prepare_bitmap_walk(&revs)) {
				count_bitmap_commit_list(&commit_count, NULL, NULL, NULL);
				printf("%d\n", commit_count);
				return 0;
