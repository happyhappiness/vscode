	if (depth > 5) {
		error("%s: ignoring alternate object stores, nesting too deep.",
				relative_base);
		return;
	}

	strbuf_addstr(&objdirbuf, absolute_path(get_object_directory()));
	normalize_path_copy(objdirbuf.buf, objdirbuf.buf);

	alt_copy = xmemdupz(alt, len);
	string_list_split_in_place(&entries, alt_copy, sep, -1);
	for (i = 0; i < entries.nr; i++) {
		const char *entry = entries.items[i].string;
