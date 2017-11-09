static int in_delta_base_cache(struct packed_git *p, off_t base_offset)
{
	return !!get_delta_base_cache_entry(p, base_offset);
}