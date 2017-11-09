int expand_ref(const char *str, int len, unsigned char *sha1, char **ref)
{
	const char **p, *r;
	int refs_found = 0;
	struct strbuf fullref = STRBUF_INIT;

	*ref = NULL;
	for (p = ref_rev_parse_rules; *p; p++) {
		unsigned char sha1_from_ref[20];
		unsigned char *this_result;
		int flag;

		this_result = refs_found ? sha1_from_ref : sha1;
		strbuf_reset(&fullref);
		strbuf_addf(&fullref, *p, len, str);
		r = resolve_ref_unsafe(fullref.buf, RESOLVE_REF_READING,
				       this_result, &flag);
		if (r) {
			if (!refs_found++)
				*ref = xstrdup(r);
			if (!warn_ambiguous_refs)
				break;
		} else if ((flag & REF_ISSYMREF) && strcmp(fullref.buf, "HEAD")) {
			warning("ignoring dangling symref %s.", fullref.buf);
		} else if ((flag & REF_ISBROKEN) && strchr(fullref.buf, '/')) {
			warning("ignoring broken ref %s.", fullref.buf);
		}
	}
	strbuf_release(&fullref);
	return refs_found;
}