static int show_head_ref(const char *refname, const unsigned char *sha1,
	int flag, void *cb_data)
{
	struct strbuf *buf = cb_data;

	if (flag & REF_ISSYMREF) {
		unsigned char unused[20];
		const char *target = resolve_ref_unsafe(refname,
							RESOLVE_REF_READING,
							unused, NULL);
		const char *target_nons = strip_namespace(target);

		strbuf_addf(buf, "ref: %s\n", target_nons);
	} else {
		strbuf_addf(buf, "%s\n", sha1_to_hex(sha1));
	}

	return 0;
}