}

#else
#define ll_find_deltas(l, s, w, d, p)	find_deltas(l, &s, w, d, p)
#endif

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

static int add_ref_tag(const char *path, const struct object_id *oid, int flag, void *cb_data)
{
	struct object_id peeled;

	if (starts_with(path, "refs/tags/") && /* is a tag? */
	    !peel_ref(path, peeled.hash)    && /* peelable? */
	    packlist_find(&to_pack, peeled.hash, NULL))      /* object packed? */
		add_tag_chain(oid);
	return 0;
}

static void prepare_pack(int window, int depth)
{
	struct object_entry **delta_list;
