static int score_trees(const unsigned char *hash1, const unsigned char *hash2)
{
	struct tree_desc one;
	struct tree_desc two;
	void *one_buf = fill_tree_desc_strict(&one, hash1);
	void *two_buf = fill_tree_desc_strict(&two, hash2);
	int score = 0;

	for (;;) {
		struct name_entry e1, e2;
		int got_entry_from_one = tree_entry(&one, &e1);
		int got_entry_from_two = tree_entry(&two, &e2);
		int cmp;

		if (got_entry_from_one && got_entry_from_two)
			cmp = base_name_entries_compare(&e1, &e2);
		else if (got_entry_from_one)
			/* two lacks this entry */
			cmp = -1;
		else if (got_entry_from_two)
			/* two has more entries */
			cmp = 1;
		else
			break;

		if (cmp < 0)
			/* path1 does not appear in two */
			score += score_missing(e1.mode, e1.path);
		else if (cmp > 0)
			/* path2 does not appear in one */
			score += score_missing(e2.mode, e2.path);
		else if (hashcmp(e1.sha1, e2.sha1))
			/* they are different */
			score += score_differs(e1.mode, e2.mode, e1.path);
		else
			/* same subtree or blob */
			score += score_matches(e1.mode, e2.mode, e1.path);
	}
	free(one_buf);
	free(two_buf);
	return score;
}