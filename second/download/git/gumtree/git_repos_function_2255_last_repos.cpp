static void *cache_or_unpack_entry(struct packed_git *p, off_t base_offset,
	unsigned long *base_size, enum object_type *type)
{
	struct delta_base_cache_entry *ent;

	ent = get_delta_base_cache_entry(p, base_offset);
	if (!ent)
		return unpack_entry(p, base_offset, type, base_size);

	if (type)
		*type = ent->type;
	if (base_size)
		*base_size = ent->size;
	return xmemdupz(ent->data, ent->size);
}