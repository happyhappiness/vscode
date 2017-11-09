static int show_ambiguous_object(const struct object_id *oid, void *data)
{
	const struct disambiguate_state *ds = data;
	struct strbuf desc = STRBUF_INIT;
	int type;


	if (ds->fn && !ds->fn(oid, ds->cb_data))
		return 0;

	type = sha1_object_info(oid->hash, NULL);
	if (type == OBJ_COMMIT) {
		struct commit *commit = lookup_commit(oid);
		if (commit) {
			struct pretty_print_context pp = {0};
			pp.date_mode.type = DATE_SHORT;
			format_commit_message(commit, " %ad - %s", &desc, &pp);
		}
	} else if (type == OBJ_TAG) {
		struct tag *tag = lookup_tag(oid);
		if (!parse_tag(tag) && tag->tag)
			strbuf_addf(&desc, " %s", tag->tag);
	}

	advise("  %s %s%s",
	       find_unique_abbrev(oid->hash, DEFAULT_ABBREV),
	       typename(type) ? typename(type) : "unknown type",
	       desc.buf);

	strbuf_release(&desc);
	return 0;
}