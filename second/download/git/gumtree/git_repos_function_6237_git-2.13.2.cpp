static int for_each_replace_name(const char **argv, each_replace_name_fn fn)
{
	const char **p, *full_hex;
	struct strbuf ref = STRBUF_INIT;
	size_t base_len;
	int had_error = 0;
	struct object_id oid;

	strbuf_addstr(&ref, git_replace_ref_base);
	base_len = ref.len;

	for (p = argv; *p; p++) {
		if (get_oid(*p, &oid)) {
			error("Failed to resolve '%s' as a valid ref.", *p);
			had_error = 1;
			continue;
		}

		strbuf_setlen(&ref, base_len);
		strbuf_addstr(&ref, oid_to_hex(&oid));
		full_hex = ref.buf + base_len;

		if (read_ref(ref.buf, oid.hash)) {
			error("replace ref '%s' not found.", full_hex);
			had_error = 1;
			continue;
		}
		if (fn(full_hex, ref.buf, &oid))
			had_error = 1;
	}
	strbuf_release(&ref);
	return had_error;
}