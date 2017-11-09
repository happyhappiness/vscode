static struct cache_entry *create_from_disk(struct ondisk_cache_entry *ondisk,
					    unsigned long *ent_size,
					    struct strbuf *previous_name)
{
	struct cache_entry *ce;
	size_t len;
	const char *name;
	unsigned int flags;

	/* On-disk flags are just 16 bits */
	flags = get_be16(&ondisk->flags);
	len = flags & CE_NAMEMASK;

	if (flags & CE_EXTENDED) {
		struct ondisk_cache_entry_extended *ondisk2;
		int extended_flags;
		ondisk2 = (struct ondisk_cache_entry_extended *)ondisk;
		extended_flags = get_be16(&ondisk2->flags2) << 16;
		/* We do not yet understand any bit out of CE_EXTENDED_FLAGS */
		if (extended_flags & ~CE_EXTENDED_FLAGS)
			die("Unknown index entry format %08x", extended_flags);
		flags |= extended_flags;
		name = ondisk2->name;
	}
	else
		name = ondisk->name;

	if (!previous_name) {
		/* v3 and earlier */
		if (len == CE_NAMEMASK)
			len = strlen(name);
		ce = cache_entry_from_ondisk(ondisk, flags, name, len);

		*ent_size = ondisk_ce_size(ce);
	} else {
		unsigned long consumed;
		consumed = expand_name_field(previous_name, name);
		ce = cache_entry_from_ondisk(ondisk, flags,
					     previous_name->buf,
					     previous_name->len);

		*ent_size = (name - ((char *)ondisk)) + consumed;
	}
	return ce;
}