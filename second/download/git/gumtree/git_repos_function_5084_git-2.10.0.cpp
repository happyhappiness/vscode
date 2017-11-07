static void find_ofs_delta_children(off_t offset,
				    int *first_index, int *last_index,
				    enum object_type type)
{
	int first = find_ofs_delta(offset, type);
	int last = first;
	int end = nr_ofs_deltas - 1;

	if (first < 0) {
		*first_index = 0;
		*last_index = -1;
		return;
	}
	while (first > 0 && ofs_deltas[first - 1].offset == offset)
		--first;
	while (last < end && ofs_deltas[last + 1].offset == offset)
		++last;
	*first_index = first;
	*last_index = last;
}