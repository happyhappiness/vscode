	*found_offset = 0;

	for (p = packed_git; p; p = p->next) {
		off_t offset = find_pack_entry_one(sha1, p);
		if (offset) {
			if (!*found_pack) {
				if (!is_pack_valid(p))
					continue;
				*found_offset = offset;
				*found_pack = p;
			}
			if (exclude)
				return 1;
			if (incremental)
