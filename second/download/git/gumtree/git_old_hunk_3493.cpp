	if (bisect_list)
		revs.limited = 1;

	if (use_bitmap_index && !revs.prune) {
		if (revs.count && !revs.left_right && !revs.cherry_mark) {
			uint32_t commit_count;
			if (!prepare_bitmap_walk(&revs)) {
				count_bitmap_commit_list(&commit_count, NULL, NULL, NULL);
				printf("%d\n", commit_count);
				return 0;
			}
		} else if (revs.tag_objects && revs.tree_objects && revs.blob_objects) {
			if (!prepare_bitmap_walk(&revs)) {
				traverse_bitmap_commit_list(&show_object_fast);
				return 0;
			}
		}
	}
