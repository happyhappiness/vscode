static void check_one_mergetag(struct commit *commit,
			       struct commit_extra_header *extra,
			       void *data)
{
	struct check_mergetag_data *mergetag_data = (struct check_mergetag_data *)data;
	const char *ref = mergetag_data->argv[0];
	struct object_id tag_oid;
	struct tag *tag;
	int i;

	hash_sha1_file(extra->value, extra->len, typename(OBJ_TAG), tag_oid.hash);
	tag = lookup_tag(tag_oid.hash);
	if (!tag)
		die(_("bad mergetag in commit '%s'"), ref);
	if (parse_tag_buffer(tag, extra->value, extra->len))
		die(_("malformed mergetag in commit '%s'"), ref);

	/* iterate over new parents */
