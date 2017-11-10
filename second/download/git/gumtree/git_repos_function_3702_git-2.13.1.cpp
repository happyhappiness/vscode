static void replace_entry(size_t pos, void *data)
{
	struct index_state *istate = data;
	struct split_index *si = istate->split_index;
	struct cache_entry *dst, *src;

	if (pos >= istate->cache_nr)
		die("position for replacement %d exceeds base index size %d",
		    (int)pos, istate->cache_nr);
	if (si->nr_replacements >= si->saved_cache_nr)
		die("too many replacements (%d vs %d)",
		    si->nr_replacements, si->saved_cache_nr);
	dst = istate->cache[pos];
	if (dst->ce_flags & CE_REMOVE)
		die("entry %d is marked as both replaced and deleted",
		    (int)pos);
	src = si->saved_cache[si->nr_replacements];
	if (ce_namelen(src))
		die("corrupt link extension, entry %d should have "
		    "zero length name", (int)pos);
	src->index = pos + 1;
	src->ce_flags |= CE_UPDATE_IN_BASE;
	src->ce_namelen = dst->ce_namelen;
	copy_cache_entry(dst, src);
	free(src);
	si->nr_replacements++;
}