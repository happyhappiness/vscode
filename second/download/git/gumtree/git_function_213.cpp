static int cat_one_file(int opt, const char *exp_type, const char *obj_name,
			int unknown_type)
{
	struct object_id oid;
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

	if (get_sha1_with_context(obj_name, 0, oid.hash, &obj_context))
		die("Not a valid object name %s", obj_name);

	if (!path)
		path = obj_context.path;
	if (obj_context.mode == S_IFINVALID)
		obj_context.mode = 0100644;

	buf = NULL;
	switch (opt) {
	case 't':
		oi.typename = &sb;
		if (sha1_object_info_extended(oid.hash, &oi, flags) < 0)
			die("git cat-file: could not get object info");
		if (sb.len) {
			printf("%s\n", sb.buf);
			strbuf_release(&sb);
			return 0;
		}
		break;

	case 's':
		oi.sizep = &size;
		if (sha1_object_info_extended(oid.hash, &oi, flags) < 0)
			die("git cat-file: could not get object info");
		printf("%lu\n", size);
		return 0;

	case 'e':
		return !has_object_file(&oid);

	case 'w':
		if (!path[0])
			die("git cat-file --filters %s: <object> must be "
			    "<sha1:path>", obj_name);

		if (filter_object(path, obj_context.mode,
				  &oid, &buf, &size))
			return -1;
		break;

	case 'c':
		if (!path[0])
			die("git cat-file --textconv %s: <object> must be <sha1:path>",
			    obj_name);

		if (textconv_object(path, obj_context.mode, &oid, 1, &buf, &size))
			break;

	case 'p':
		type = sha1_object_info(oid.hash, NULL);
		if (type < 0)
			die("Not a valid object name %s", obj_name);

		/* custom pretty-print here */
		if (type == OBJ_TREE) {
			const char *ls_args[3] = { NULL };
			ls_args[0] =  "ls-tree";
			ls_args[1] =  obj_name;
			return cmd_ls_tree(2, ls_args, NULL);
		}

		if (type == OBJ_BLOB)
			return stream_blob_to_fd(1, &oid, NULL, 0);
		buf = read_sha1_file(oid.hash, &type, &size);
		if (!buf)
			die("Cannot read object %s", obj_name);

		/* otherwise just spit out the data */
		break;

	case 0:
		if (type_from_string(exp_type) == OBJ_BLOB) {
			struct object_id blob_oid;
			if (sha1_object_info(oid.hash, NULL) == OBJ_TAG) {
				char *buffer = read_sha1_file(oid.hash, &type, &size);
				const char *target;
				if (!skip_prefix(buffer, "object ", &target) ||
				    get_oid_hex(target, &blob_oid))
					die("%s not a valid tag", oid_to_hex(&oid));
				free(buffer);
			} else
				oidcpy(&blob_oid, &oid);

			if (sha1_object_info(blob_oid.hash, NULL) == OBJ_BLOB)
				return stream_blob_to_fd(1, &blob_oid, NULL, 0);
			/*
			 * we attempted to dereference a tag to a blob
			 * and failed; there may be new dereference
			 * mechanisms this code is not aware of.
			 * fall-back to the usual case.
			 */
		}
		buf = read_object_with_reference(oid.hash, exp_type, &size, NULL);
		break;

	default:
		die("git cat-file: unknown option: %s", exp_type);
	}

	if (!buf)
		die("git cat-file %s: bad file", obj_name);

	write_or_die(1, buf, size);
	return 0;
}