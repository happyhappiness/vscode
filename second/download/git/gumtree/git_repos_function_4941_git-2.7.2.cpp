static void find_ref_delta_children(const unsigned char *sha1,
				    int *first_index, int *last_index,
				    enum object_type type)
{
	int first = find_ref_delta(sha1, type);
	int last = first;
	int end = nr_ref_deltas - 1;

	if (first < 0) {
		*first_index = 0;
		*last_index = -1;
		return;
	}
	while (first > 0 && !hashcmp(ref_deltas[first - 1].sha1, sha1))
		--first;
	while (last < end && !hashcmp(ref_deltas[last + 1].sha1, sha1))
		++last;
	*first_index = first;
	*last_index = last;
}