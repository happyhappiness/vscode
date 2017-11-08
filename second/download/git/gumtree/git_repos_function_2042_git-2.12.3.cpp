unsigned long approximate_object_count(void)
{
	static unsigned long count;
	if (!approximate_object_count_valid) {
		struct packed_git *p;

		prepare_packed_git();
		count = 0;
		for (p = packed_git; p; p = p->next) {
			if (open_pack_index(p))
				continue;
			count += p->num_objects;
		}
	}
	return count;
}