static int register_ref(const char *refname, const struct object_id *oid,
			int flags, void *cb_data)
{
	struct strbuf good_prefix = STRBUF_INIT;
	strbuf_addstr(&good_prefix, term_good);
	strbuf_addstr(&good_prefix, "-");

	if (!strcmp(refname, term_bad)) {
		current_bad_oid = xmalloc(sizeof(*current_bad_oid));
		oidcpy(current_bad_oid, oid);
	} else if (starts_with(refname, good_prefix.buf)) {
		oid_array_append(&good_revs, oid);
	} else if (starts_with(refname, "skip-")) {
		oid_array_append(&skipped_revs, oid);
	}

	strbuf_release(&good_prefix);

	return 0;
}