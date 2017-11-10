static int ce_write_entry(git_SHA_CTX *c, int fd, struct cache_entry *ce,
			  struct strbuf *previous_name)
{
	int size;
	struct ondisk_cache_entry *ondisk;
	int saved_namelen = saved_namelen; /* compiler workaround */
	char *name;
	int result;

	if (ce->ce_flags & CE_STRIP_NAME) {
		saved_namelen = ce_namelen(ce);
		ce->ce_namelen = 0;
	}

	if (!previous_name) {
		size = ondisk_ce_size(ce);
		ondisk = xcalloc(1, size);
		name = copy_cache_entry_to_ondisk(ondisk, ce);
		memcpy(name, ce->name, ce_namelen(ce));
	} else {
		int common, to_remove, prefix_size;
		unsigned char to_remove_vi[16];
		for (common = 0;
		     (ce->name[common] &&
		      common < previous_name->len &&
		      ce->name[common] == previous_name->buf[common]);
		     common++)
			; /* still matching */
		to_remove = previous_name->len - common;
		prefix_size = encode_varint(to_remove, to_remove_vi);

		if (ce->ce_flags & CE_EXTENDED)
			size = offsetof(struct ondisk_cache_entry_extended, name);
		else
			size = offsetof(struct ondisk_cache_entry, name);
		size += prefix_size + (ce_namelen(ce) - common + 1);

		ondisk = xcalloc(1, size);
		name = copy_cache_entry_to_ondisk(ondisk, ce);
		memcpy(name, to_remove_vi, prefix_size);
		memcpy(name + prefix_size, ce->name + common, ce_namelen(ce) - common);

		strbuf_splice(previous_name, common, to_remove,
			      ce->name + common, ce_namelen(ce) - common);
	}
	if (ce->ce_flags & CE_STRIP_NAME) {
		ce->ce_namelen = saved_namelen;
		ce->ce_flags &= ~CE_STRIP_NAME;
	}

	result = ce_write(c, fd, ondisk, size);
	free(ondisk);
	return result;
}