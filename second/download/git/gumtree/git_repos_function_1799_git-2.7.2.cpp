static struct delta_base_cache_entry *
get_delta_base_cache_entry(struct packed_git *p, off_t base_offset)
{
	unsigned long hash = pack_entry_hash(p, base_offset);
	return delta_base_cache + hash;
}