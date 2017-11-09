static int find_identical_files(struct hashmap *srcs,
				int dst_index,
				struct diff_options *options)
{
	int renames = 0;

	struct diff_filespec *target = rename_dst[dst_index].two;
	struct file_similarity *p, *best = NULL;
	int i = 100, best_score = -1;

	/*
	 * Find the best source match for specified destination.
	 */
	p = hashmap_get_from_hash(srcs, hash_filespec(target), NULL);
	for (; p; p = hashmap_get_next(srcs, p)) {
		int score;
		struct diff_filespec *source = p->filespec;

		/* False hash collision? */
		if (oidcmp(&source->oid, &target->oid))
			continue;
		/* Non-regular files? If so, the modes must match! */
		if (!S_ISREG(source->mode) || !S_ISREG(target->mode)) {
			if (source->mode != target->mode)
				continue;
		}
		/* Give higher scores to sources that haven't been used already */
		score = !source->rename_used;
		if (source->rename_used && options->detect_rename != DIFF_DETECT_COPY)
			continue;
		score += basename_same(source, target);
		if (score > best_score) {
			best = p;
			best_score = score;
			if (score == 2)
				break;
		}

		/* Too many identical alternatives? Pick one */
		if (!--i)
			break;
	}
	if (best) {
		record_rename_pair(dst_index, best->index, MAX_SCORE);
		renames++;
	}
	return renames;
}