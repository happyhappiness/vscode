static void match_trees(const struct object_id *hash1,
			const struct object_id *hash2,
			int *best_score,
			char **best_match,
			const char *base,
			int recurse_limit)
{
	struct tree_desc one;
	void *one_buf = fill_tree_desc_strict(&one, hash1);

	while (one.size) {
		const char *path;
		const struct object_id *elem;
		unsigned mode;
		int score;

		elem = tree_entry_extract(&one, &path, &mode);
		if (!S_ISDIR(mode))
			goto next;
		score = score_trees(elem, hash2);
		if (*best_score < score) {
			free(*best_match);
			*best_match = xstrfmt("%s%s", base, path);
			*best_score = score;
		}
		if (recurse_limit) {
			char *newbase = xstrfmt("%s%s/", base, path);
			match_trees(elem, hash2, best_score, best_match,
				    newbase, recurse_limit - 1);
			free(newbase);
		}

	next:
		update_tree_entry(&one);
	}
	free(one_buf);
}