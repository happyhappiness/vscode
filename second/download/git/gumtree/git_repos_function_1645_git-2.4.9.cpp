static int in_delta_base_cache(struct packed_git *p, off_t base_offset)
{
	struct delta_base_cache_entry *ent;
	ent = get_delta_base_cache_entry(p, base_offset);
	return eq_delta_base_cache_entry(ent, p, base_offset);
}