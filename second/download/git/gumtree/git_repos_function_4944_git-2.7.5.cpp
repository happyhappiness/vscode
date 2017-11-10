static int find_ofs_delta(const off_t offset, enum object_type type)
{
	int first = 0, last = nr_ofs_deltas;

	while (first < last) {
		int next = (first + last) / 2;
		struct ofs_delta_entry *delta = &ofs_deltas[next];
		int cmp;

		cmp = compare_ofs_delta_bases(offset, delta->offset,
					      type, objects[delta->obj_no].type);
		if (!cmp)
			return next;
		if (cmp < 0) {
			last = next;
			continue;
		}
		first = next+1;
	}
	return -first-1;
}