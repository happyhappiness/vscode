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
