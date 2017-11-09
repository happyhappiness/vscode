static void link_alt_odb_entries(const char *alt, int len, int sep,
				 const char *relative_base, int depth)
{
	struct strbuf objdirbuf = STRBUF_INIT;
	struct strbuf entry = STRBUF_INIT;

	if (depth > 5) {
		error("%s: ignoring alternate object stores, nesting too deep.",
				relative_base);
		return;
	}

	strbuf_add_absolute_path(&objdirbuf, get_object_directory());
	if (strbuf_normalize_path(&objdirbuf) < 0)
		die("unable to normalize object directory: %s",
		    objdirbuf.buf);

	while (*alt) {
		alt = parse_alt_odb_entry(alt, sep, &entry);
		if (!entry.len)
			continue;
		link_alt_odb_entry(entry.buf, relative_base, depth, objdirbuf.buf);
	}
	strbuf_release(&entry);
	strbuf_release(&objdirbuf);
}