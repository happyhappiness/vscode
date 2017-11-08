static inline void copy_cache_entry(struct cache_entry *dst,
				    const struct cache_entry *src)
{
	unsigned int state = dst->ce_flags & CE_HASHED;

	/* Don't copy hash chain and name */
	memcpy(&dst->ce_stat_data, &src->ce_stat_data,
			offsetof(struct cache_entry, name) -
			offsetof(struct cache_entry, ce_stat_data));

	/* Restore the hash state */
	dst->ce_flags = (dst->ce_flags & ~CE_HASHED) | state;
}