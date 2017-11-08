static int delta_base_cache_key_eq(const struct delta_base_cache_key *a,
				   const struct delta_base_cache_key *b)
{
	return a->p == b->p && a->base_offset == b->base_offset;
}