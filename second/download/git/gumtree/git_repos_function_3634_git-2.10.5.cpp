void shift_tree(const struct object_id *hash1,
		const struct object_id *hash2,
		struct object_id *shifted,
		int depth_limit)
{
	char *add_prefix;
	char *del_prefix;
	int add_score, del_score;

	/*
	 * NEEDSWORK: this limits the recursion depth to hardcoded
	 * value '2' to avoid excessive overhead.
	 */
	if (!depth_limit)
		depth_limit = 2;

	add_score = del_score = score_trees(hash1, hash2);
	add_prefix = xcalloc(1, 1);
	del_prefix = xcalloc(1, 1);

	/*
	 * See if one's subtree resembles two; if so we need to prefix
	 * two with a few fake trees to match the prefix.
	 */
	match_trees(hash1, hash2, &add_score, &add_prefix, "", depth_limit);

	/*
	 * See if two's subtree resembles one; if so we need to
	 * pick only subtree of two.
	 */
	match_trees(hash2, hash1, &del_score, &del_prefix, "", depth_limit);

	/* Assume we do not have to do any shifting */
	oidcpy(shifted, hash2);

	if (add_score < del_score) {
		/* We need to pick a subtree of two */
		unsigned mode;

		if (!*del_prefix)
			return;

		if (get_tree_entry(hash2->hash, del_prefix, shifted->hash, &mode))
			die("cannot find path %s in tree %s",
			    del_prefix, oid_to_hex(hash2));
		return;
	}

	if (!*add_prefix)
		return;

	splice_tree(hash1->hash, add_prefix, hash2->hash, shifted->hash);
}