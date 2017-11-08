static int want_object_in_pack(const unsigned char *sha1,
			       int exclude,
			       struct packed_git **found_pack,
			       off_t *found_offset)
{
	struct mru_entry *entry;
	int want;

	if (!exclude && local && has_loose_object_nonlocal(sha1))
		return 0;

	/*
	 * If we already know the pack object lives in, start checks from that
	 * pack - in the usual case when neither --local was given nor .keep files
	 * are present we will determine the answer right now.
	 */
	if (*found_pack) {
		want = want_found_object(exclude, *found_pack);
		if (want != -1)
			return want;
	}

	for (entry = packed_git_mru->head; entry; entry = entry->next) {
		struct packed_git *p = entry->item;
		off_t offset;

		if (p == *found_pack)
			offset = *found_offset;
		else
			offset = find_pack_entry_one(sha1, p);

		if (offset) {
			if (!*found_pack) {
				if (!is_pack_valid(p))
					continue;
				*found_offset = offset;
				*found_pack = p;
			}
			want = want_found_object(exclude, p);
			if (!exclude && want > 0)
				mru_mark(packed_git_mru, entry);
			if (want != -1)
				return want;
		}
	}

	return 1;
}