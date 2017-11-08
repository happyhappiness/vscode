static int cat_one_file(int opt, const char *exp_type, const char *obj_name)
{
	unsigned char sha1[20];
	enum object_type type;
	char *buf;
	unsigned long size;
	struct object_context obj_context;

	if (get_sha1_with_context(obj_name, 0, sha1, &obj_context))
		die("Not a valid object name %s", obj_name);

	buf = NULL;
	switch (opt) {
	case 't':
		type = sha1_object_info(sha1, NULL);
		if (type > 0) {
			printf("%s\n", typename(type));
			return 0;
		}
		break;

	case 's':
		type = sha1_object_info(sha1, &size);
		if (type > 0) {
			printf("%lu\n", size);
			return 0;
		}
		break;

	case 'e':
		return !has_sha1_file(sha1);

	case 'c':
		if (!obj_context.path[0])
			die("git cat-file --textconv %s: <object> must be <sha1:path>",
			    obj_name);

		if (textconv_object(obj_context.path, obj_context.mode, sha1, 1, &buf, &size))
			break;

	case 'p':
		type = sha1_object_info(sha1, NULL);
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
			return stream_blob_to_fd(1, sha1, NULL, 0);
		buf = read_sha1_file(sha1, &type, &size);
		if (!buf)
			die("Cannot read object %s", obj_name);

		/* otherwise just spit out the data */
		break;

	case 0:
		if (type_from_string(exp_type) == OBJ_BLOB) {
			unsigned char blob_sha1[20];
			if (sha1_object_info(sha1, NULL) == OBJ_TAG) {
				char *buffer = read_sha1_file(sha1, &type, &size);
				const char *target;
				if (!skip_prefix(buffer, "object ", &target) ||
				    get_sha1_hex(target, blob_sha1))
					die("%s not a valid tag", sha1_to_hex(sha1));
				free(buffer);
			} else
				hashcpy(blob_sha1, sha1);

			if (sha1_object_info(blob_sha1, NULL) == OBJ_BLOB)
				return stream_blob_to_fd(1, blob_sha1, NULL, 0);
			/*
			 * we attempted to dereference a tag to a blob
			 * and failed; there may be new dereference
			 * mechanisms this code is not aware of.
			 * fall-back to the usual case.
			 */
		}
		buf = read_object_with_reference(sha1, exp_type, &size, NULL);
		break;

	default:
		die("git cat-file: unknown option: %s", exp_type);
	}

	if (!buf)
		die("git cat-file %s: bad file", obj_name);

	write_or_die(1, buf, size);
	return 0;
}