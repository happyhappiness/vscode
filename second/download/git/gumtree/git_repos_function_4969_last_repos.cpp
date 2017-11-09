static int for_each_tag_name(const char **argv, each_tag_name_fn fn,
			     const void *cb_data)
{
	const char **p;
	struct strbuf ref = STRBUF_INIT;
	int had_error = 0;
	struct object_id oid;

	for (p = argv; *p; p++) {
		strbuf_reset(&ref);
		strbuf_addf(&ref, "refs/tags/%s", *p);
		if (read_ref(ref.buf, oid.hash)) {
			error(_("tag '%s' not found."), *p);
			had_error = 1;
			continue;
		}
		if (fn(*p, ref.buf, &oid, cb_data))
			had_error = 1;
	}
	strbuf_release(&ref);
	return had_error;
}