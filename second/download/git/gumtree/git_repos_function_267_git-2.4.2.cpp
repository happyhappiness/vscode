static int ce_compare_link(const struct cache_entry *ce, size_t expected_size)
{
	int match = -1;
	void *buffer;
	unsigned long size;
	enum object_type type;
	struct strbuf sb = STRBUF_INIT;

	if (strbuf_readlink(&sb, ce->name, expected_size))
		return -1;

	buffer = read_sha1_file(ce->sha1, &type, &size);
	if (buffer) {
		if (size == sb.len)
			match = memcmp(buffer, sb.buf, size);
		free(buffer);
	}
	strbuf_release(&sb);
	return match;
}