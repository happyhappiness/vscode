	enum object_type type;
	char *buf;
	unsigned long size;
	struct object_context obj_context;
	struct object_info oi = OBJECT_INFO_INIT;
	struct strbuf sb = STRBUF_INIT;
	unsigned flags = LOOKUP_REPLACE_OBJECT;
	const char *path = force_path;

	if (unknown_type)
		flags |= LOOKUP_UNKNOWN_OBJECT;

	if (get_sha1_with_context(obj_name, GET_SHA1_RECORD_PATH,
				  oid.hash, &obj_context))
		die("Not a valid object name %s", obj_name);

	if (!path)
