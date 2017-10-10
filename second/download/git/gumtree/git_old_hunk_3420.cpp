	 * See if two's subtree resembles one; if so we need to
	 * pick only subtree of two.
	 */
	match_trees(hash2, hash1, &del_score, &del_prefix, "", depth_limit);

	/* Assume we do not have to do any shifting */
	hashcpy(shifted, hash2);

	if (add_score < del_score) {
		/* We need to pick a subtree of two */
		unsigned mode;

		if (!*del_prefix)
			return;

		if (get_tree_entry(hash2, del_prefix, shifted, &mode))
			die("cannot find path %s in tree %s",
			    del_prefix, sha1_to_hex(hash2));
		return;
	}

	if (!*add_prefix)
		return;

	splice_tree(hash1, add_prefix, hash2, shifted);
}

/*
 * The user says the trees will be shifted by this much.
 * Unfortunately we cannot fundamentally tell which one to
 * be prefixed, as recursive merge can work in either direction.
 */
void shift_tree_by(const unsigned char *hash1,
		   const unsigned char *hash2,
		   unsigned char *shifted,
		   const char *shift_prefix)
{
	unsigned char sub1[20], sub2[20];
	unsigned mode1, mode2;
	unsigned candidate = 0;

	/* Can hash2 be a tree at shift_prefix in tree hash1? */
	if (!get_tree_entry(hash1, shift_prefix, sub1, &mode1) &&
	    S_ISDIR(mode1))
		candidate |= 1;

	/* Can hash1 be a tree at shift_prefix in tree hash2? */
	if (!get_tree_entry(hash2, shift_prefix, sub2, &mode2) &&
	    S_ISDIR(mode2))
		candidate |= 2;

	if (candidate == 3) {
		/* Both are plausible -- we need to evaluate the score */
		int best_score = score_trees(hash1, hash2);
		int score;

		candidate = 0;
		score = score_trees(sub1, hash2);
		if (score > best_score) {
			candidate = 1;
			best_score = score;
		}
		score = score_trees(sub2, hash1);
		if (score > best_score)
			candidate = 2;
	}

	if (!candidate) {
		/* Neither is plausible -- do not shift */
		hashcpy(shifted, hash2);
		return;
	}

	if (candidate == 1)
		/*
		 * shift tree2 down by adding shift_prefix above it
		 * to match tree1.
		 */
		splice_tree(hash1, shift_prefix, hash2, shifted);
	else
		/*
		 * shift tree2 up by removing shift_prefix from it
		 * to match tree1.
		 */
		hashcpy(shifted, sub2);
}
