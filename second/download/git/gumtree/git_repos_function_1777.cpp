static int find_pack_entry(const unsigned char *sha1, struct pack_entry *e)
{
	struct packed_git *p;

	prepare_packed_git();
	if (!packed_git)
		return 0;

	if (last_found_pack && fill_pack_entry(sha1, e, last_found_pack))
		return 1;

	for (p = packed_git; p; p = p->next) {
		if (p == last_found_pack)
			continue; /* we already checked this one */

		if (fill_pack_entry(sha1, e, p)) {
			last_found_pack = p;
			return 1;
		}
	}
	return 0;
}