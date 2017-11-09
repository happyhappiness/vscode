static struct object_entry *dereference(struct object_entry *oe,
					struct object_id *oid)
{
	unsigned long size;
	char *buf = NULL;
	if (!oe) {
		enum object_type type = sha1_object_info(oid->hash, NULL);
		if (type < 0)
			die("object not found: %s", oid_to_hex(oid));
		/* cache it! */
		oe = insert_object(oid);
		oe->type = type;
		oe->pack_id = MAX_PACK_ID;
		oe->idx.offset = 1;
	}
	switch (oe->type) {
	case OBJ_TREE:	/* easy case. */
		return oe;
	case OBJ_COMMIT:
	case OBJ_TAG:
		break;
	default:
		die("Not a tree-ish: %s", command_buf.buf);
	}

	if (oe->pack_id != MAX_PACK_ID) {	/* in a pack being written */
		buf = gfi_unpack_entry(oe, &size);
	} else {
		enum object_type unused;
		buf = read_sha1_file(oid->hash, &unused, &size);
	}
	if (!buf)
		die("Can't load object %s", oid_to_hex(oid));

	/* Peel one layer. */
	switch (oe->type) {
	case OBJ_TAG:
		if (size < GIT_SHA1_HEXSZ + strlen("object ") ||
		    get_oid_hex(buf + strlen("object "), oid))
			die("Invalid SHA1 in tag: %s", command_buf.buf);
		break;
	case OBJ_COMMIT:
		if (size < GIT_SHA1_HEXSZ + strlen("tree ") ||
		    get_oid_hex(buf + strlen("tree "), oid))
			die("Invalid SHA1 in commit: %s", command_buf.buf);
	}

	free(buf);
	return find_object(oid);
}