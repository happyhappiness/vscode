static struct cache_entry *dup_entry(const struct cache_entry *ce)
{
	unsigned int size = ce_size(ce);
	struct cache_entry *new = xmalloc(size);

	memcpy(new, ce, size);
	return new;
}