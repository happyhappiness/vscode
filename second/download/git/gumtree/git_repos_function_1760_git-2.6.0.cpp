static void *cache_or_unpack_entry(struct packed_git *p, off_t base_offset,
	unsigned long *base_size, enum object_type *type, int keep_cache)
{
	struct delta_base_cache_entry *ent;
	void *ret;

	ent = get_delta_base_cache_entry(p, base_offset);

	if (!eq_delta_base_cache_entry(ent, p, base_offset))
		return unpack_entry(p, base_offset, type, base_size);

	ret = ent->data;

	if (!keep_cache)
		clear_delta_base_cache_entry(ent);
	else
		ret = xmemdupz(ent->data, ent->size);
	*type = ent->type;
	*base_size = ent->size;
	return ret;
}