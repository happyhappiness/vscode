struct object *parse_object(const unsigned char *sha1)
{
	unsigned long size;
	enum object_type type;
	int eaten;
	const unsigned char *repl = lookup_replace_object(sha1);
	void *buffer;
	struct object *obj;

	obj = lookup_object(sha1);
	if (obj && obj->parsed)
		return obj;

	if ((obj && obj->type == OBJ_BLOB) ||
	    (!obj && has_sha1_file(sha1) &&
	     sha1_object_info(sha1, NULL) == OBJ_BLOB)) {
		if (check_sha1_signature(repl, NULL, 0, NULL) < 0) {
			error("sha1 mismatch %s", sha1_to_hex(repl));
			return NULL;
		}
		parse_blob_buffer(lookup_blob(sha1), NULL, 0);
		return lookup_object(sha1);
	}

	buffer = read_sha1_file(sha1, &type, &size);
	if (buffer) {
		if (check_sha1_signature(repl, buffer, size, typename(type)) < 0) {
			free(buffer);
			error("sha1 mismatch %s", sha1_to_hex(repl));
			return NULL;
		}

		obj = parse_object_buffer(sha1, type, size, buffer, &eaten);
		if (!eaten)
			free(buffer);
		return obj;
	}
	return NULL;
}