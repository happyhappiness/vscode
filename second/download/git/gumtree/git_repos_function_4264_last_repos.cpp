static void find_short_packed_object(struct disambiguate_state *ds)
{
	struct packed_git *p;

	prepare_packed_git();
	for (p = packed_git; p && !ds->ambiguous; p = p->next)
		unique_in_pack(p, ds);
}