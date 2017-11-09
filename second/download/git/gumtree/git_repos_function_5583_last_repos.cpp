static int find_ref_delta(const unsigned char *sha1, enum object_type type)
{
	int first = 0, last = nr_ref_deltas;

	while (first < last) {
		int next = (first + last) / 2;
		struct ref_delta_entry *delta = &ref_deltas[next];
		int cmp;

		cmp = compare_ref_delta_bases(sha1, delta->sha1,
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