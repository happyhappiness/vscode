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

