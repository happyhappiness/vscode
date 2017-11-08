static int too_many_packs(void)
{
	struct packed_git *p;
	int cnt;

	if (gc_auto_pack_limit <= 0)
		return 0;

	prepare_packed_git();
	for (cnt = 0, p = packed_git; p; p = p->next) {
		if (!p->pack_local)
			continue;
		if (p->pack_keep)
			continue;
		/*
		 * Perhaps check the size of the pack and count only
		 * very small ones here?
		 */
		cnt++;
	}
	return gc_auto_pack_limit < cnt;
}