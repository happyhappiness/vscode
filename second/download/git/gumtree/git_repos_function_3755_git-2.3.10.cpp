static struct notes_merge_pair *find_notes_merge_pair_pos(
		struct notes_merge_pair *list, int len, unsigned char *obj,
		int insert_new, int *occupied)
{
	/*
	 * Both diff_tree_remote() and diff_tree_local() tend to process
	 * merge_pairs in ascending order. Therefore, cache last returned
	 * index, and search sequentially from there until the appropriate
	 * position is found.
	 *
	 * Since inserts only happen from diff_tree_remote() (which mainly
	 * _appends_), we don't care that inserting into the middle of the
	 * list is expensive (using memmove()).
	 */
	static int last_index;
	int i = last_index < len ? last_index : len - 1;
	int prev_cmp = 0, cmp = -1;
	while (i >= 0 && i < len) {
		cmp = hashcmp(obj, list[i].obj);
		if (!cmp) /* obj belongs @ i */
			break;
		else if (cmp < 0 && prev_cmp <= 0) /* obj belongs < i */
			i--;
		else if (cmp < 0) /* obj belongs between i-1 and i */
			break;
		else if (cmp > 0 && prev_cmp >= 0) /* obj belongs > i */
			i++;
		else /* if (cmp > 0) */ { /* obj belongs between i and i+1 */
			i++;
			break;
		}
		prev_cmp = cmp;
	}
	if (i < 0)
		i = 0;
	/* obj belongs at, or immediately preceding, index i (0 <= i <= len) */

	if (!cmp)
		*occupied = 1;
	else {
		*occupied = 0;
		if (insert_new && i < len) {
			memmove(list + i + 1, list + i,
				(len - i) * sizeof(struct notes_merge_pair));
			memset(list + i, 0, sizeof(struct notes_merge_pair));
		}
	}
	last_index = i;
	return list + i;
}