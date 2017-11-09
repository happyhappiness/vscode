int for_each_glob_ref_in(each_ref_fn fn, const char *pattern,
	const char *prefix, void *cb_data)
{
	struct strbuf real_pattern = STRBUF_INIT;
	struct ref_filter filter;
	int ret;

	if (!prefix && !starts_with(pattern, "refs/"))
		strbuf_addstr(&real_pattern, "refs/");
	else if (prefix)
		strbuf_addstr(&real_pattern, prefix);
	strbuf_addstr(&real_pattern, pattern);

	if (!has_glob_specials(pattern)) {
		/* Append implied '/' '*' if not present. */
		strbuf_complete(&real_pattern, '/');
		/* No need to check for '*', there is none. */
		strbuf_addch(&real_pattern, '*');
	}

	filter.pattern = real_pattern.buf;
	filter.fn = fn;
	filter.cb_data = cb_data;
	ret = for_each_ref(filter_refs, &filter);

	strbuf_release(&real_pattern);
	return ret;
}