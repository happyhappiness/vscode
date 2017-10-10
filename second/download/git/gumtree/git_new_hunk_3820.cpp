
	/* PHASE 2: handle the base */
	switch (type) {
	case OBJ_OFS_DELTA:
	case OBJ_REF_DELTA:
		if (data)
			die("BUG: unpack_entry: left loop at a valid delta");
		break;
	case OBJ_COMMIT:
	case OBJ_TREE:
	case OBJ_BLOB:
	case OBJ_TAG:
		if (!base_from_cache)
