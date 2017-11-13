struct pack_revindex *revindex_for_pack(struct packed_git *p)
{
	int num;
	struct pack_revindex *rix;

	if (!pack_revindex_hashsz)
		init_pack_revindex();

	num = pack_revindex_ix(p);
	if (num < 0)
		die("internal error: pack revindex fubar");

	rix = &pack_revindex[num];
	if (!rix->revindex)
		create_pack_revindex(rix);

	return rix;
}