static void init_pack_revindex(void)
{
	int num;
	struct packed_git *p;

	for (num = 0, p = packed_git; p; p = p->next)
		num++;
	if (!num)
		return;
	pack_revindex_hashsz = num * 11;
	pack_revindex = xcalloc(pack_revindex_hashsz, sizeof(*pack_revindex));
	for (p = packed_git; p; p = p->next) {
		num = pack_revindex_ix(p);
		num = - 1 - num;
		pack_revindex[num].p = p;
	}
	/* revindex elements are lazily initialized */
}