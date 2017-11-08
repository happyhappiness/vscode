static int eq_delta_base_cache_entry(struct delta_base_cache_entry *ent,
				     struct packed_git *p, off_t base_offset)
{
	return (ent->data && ent->p == p && ent->base_offset == base_offset);
}