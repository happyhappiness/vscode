void load_pack_revindex(struct packed_git *p)
{
	if (!p->revindex)
		create_pack_revindex(p);
}