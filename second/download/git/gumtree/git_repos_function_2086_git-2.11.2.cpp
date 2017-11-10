static int find_pack_entry(const unsigned char *sha1, struct pack_entry *e)
{
	struct mru_entry *p;

	prepare_packed_git();
	if (!packed_git)
		return 0;

	for (p = packed_git_mru->head; p; p = p->next) {
		if (fill_pack_entry(sha1, e, p->item)) {
			mru_mark(packed_git_mru, p);
			return 1;
		}
	}
	return 0;
}