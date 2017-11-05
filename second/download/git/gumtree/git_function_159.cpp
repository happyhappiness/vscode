static void add_tag_chain(const struct object_id *oid)
{
	struct tag *tag;

	/*
	 * We catch duplicates already in add_object_entry(), but we'd
	 * prefer to do this extra check to avoid having to parse the
	 * tag at all if we already know that it's being packed (e.g., if
	 * it was included via bitmaps, we would not have parsed it
	 * previously).
	 */
	if (packlist_find(&to_pack, oid->hash, NULL))
		return;

	tag = lookup_tag(oid->hash);
	while (1) {
		if (!tag || parse_tag(tag) || !tag->tagged)
			die("unable to pack objects reachable from tag %s",
			    oid_to_hex(oid));

		add_object_entry(tag->object.oid.hash, OBJ_TAG, NULL, 0);

		if (tag->tagged->type != OBJ_TAG)
			return;

		tag = (struct tag *)tag->tagged;
	}
}