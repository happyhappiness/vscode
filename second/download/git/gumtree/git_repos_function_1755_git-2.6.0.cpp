static unsigned long pack_entry_hash(struct packed_git *p, off_t base_offset)
{
	unsigned long hash;

	hash = (unsigned long)p + (unsigned long)base_offset;
	hash += (hash >> 8) + (hash >> 16);
	return hash % MAX_DELTA_CACHE;
}