	 * We do not want to call parse_object here, because
	 * inflating blobs and trees could be very expensive.
	 * However, we do need to know the correct type for
	 * later processing, and the revision machinery expects
	 * commits and tags to have been parsed.
	 */
	type = sha1_object_info(sha1, NULL);
	if (type < 0)
		die("unable to get object info for %s", sha1_to_hex(sha1));

	switch (type) {
	case OBJ_TAG:
	case OBJ_COMMIT:
		obj = parse_object_or_die(sha1, NULL);
		break;
	case OBJ_TREE:
		obj = (struct object *)lookup_tree(sha1);
		break;
	case OBJ_BLOB:
		obj = (struct object *)lookup_blob(sha1);
		break;
	default:
		die("unknown object type for %s: %s",
		    sha1_to_hex(sha1), typename(type));
	}

	if (!obj)
		die("unable to lookup %s", sha1_to_hex(sha1));

	add_pending_object(data->revs, obj, "");
}

static int add_recent_loose(const unsigned char *sha1,
			    const char *path, void *data)
{
	struct stat st;
	struct object *obj = lookup_object(sha1);

	if (obj && obj->flags & SEEN)
		return 0;

	if (stat(path, &st) < 0) {
		/*
