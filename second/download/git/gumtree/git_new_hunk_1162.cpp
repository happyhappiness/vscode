	unsigned flags = LOOKUP_REPLACE_OBJECT;
	const char *path = force_path;

	if (unknown_type)
		flags |= LOOKUP_UNKNOWN_OBJECT;

	if (get_sha1_with_context(obj_name, GET_SHA1_RECORD_PATH,
				  oid.hash, &obj_context))
		die("Not a valid object name %s", obj_name);

	if (!path)
		path = obj_context.path;
	if (obj_context.mode == S_IFINVALID)
		obj_context.mode = 0100644;
