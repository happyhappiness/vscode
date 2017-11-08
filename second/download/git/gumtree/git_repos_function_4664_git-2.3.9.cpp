static void find_delta_children(const union delta_base *base,
				int *first_index, int *last_index,
				enum object_type type)
{
	int first = find_delta(base, type);
	int last = first;
	int end = nr_deltas - 1;

	if (first < 0) {
		*first_index = 0;
		*last_index = -1;
		return;
	}
	while (first > 0 && !memcmp(&deltas[first - 1].base, base, UNION_BASE_SZ))
		--first;
	while (last < end && !memcmp(&deltas[last + 1].base, base, UNION_BASE_SZ))
		++last;
	*first_index = first;
	*last_index = last;
}