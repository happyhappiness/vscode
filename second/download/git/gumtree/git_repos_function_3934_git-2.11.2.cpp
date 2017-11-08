static int show_ambiguous_object(const unsigned char *sha1, void *data)
{
	const struct disambiguate_state *ds = data;
	struct strbuf desc = STRBUF_INIT;
	int type;

	if (ds->fn && !ds->fn(sha1, ds->cb_data))
		return 0;

	type = sha1_object_info(sha1, NULL);
	if (type == OBJ_COMMIT) {
		struct commit *commit = lookup_commit(sha1);
		if (commit) {
			struct pretty_print_context pp = {0};
			pp.date_mode.type = DATE_SHORT;
			format_commit_message(commit, " %ad - %s", &desc, &pp);
		}
	} else if (type == OBJ_TAG) {
		struct tag *tag = lookup_tag(sha1);
		if (!parse_tag(tag) && tag->tag)
			strbuf_addf(&desc, " %s", tag->tag);
	}

	advise("  %s %s%s",
	       find_unique_abbrev(sha1, DEFAULT_ABBREV),
	       typename(type) ? typename(type) : "unknown type",
	       desc.buf);

	strbuf_release(&desc);
	return 0;
}