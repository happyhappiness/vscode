	 * We do not want to call parse_object here, because
	 * inflating blobs and trees could be very expensive.
	 * However, we do need to know the correct type for
	 * later processing, and the revision machinery expects
	 * commits and tags to have been parsed.
	 */
	type = sha1_object_info(oid->hash, NULL);
	if (type < 0)
		die("unable to get object info for %s", oid_to_hex(oid));

	switch (type) {
	case OBJ_TAG:
	case OBJ_COMMIT:
		obj = parse_object_or_die(oid->hash, NULL);
		break;
	case OBJ_TREE:
		obj = (struct object *)lookup_tree(oid->hash);
		break;
	case OBJ_BLOB:
		obj = (struct object *)lookup_blob(oid->hash);
		break;
	default:
		die("unknown object type for %s: %s",
		    oid_to_hex(oid), typename(type));
	}

	if (!obj)
		die("unable to lookup %s", oid_to_hex(oid));

	add_pending_object(data->revs, obj, "");
}

static int add_recent_loose(const struct object_id *oid,
			    const char *path, void *data)
{
	struct stat st;
	struct object *obj = lookup_object(oid->hash);

	if (obj && obj->flags & SEEN)
		return 0;

	if (stat(path, &st) < 0) {
		/*
