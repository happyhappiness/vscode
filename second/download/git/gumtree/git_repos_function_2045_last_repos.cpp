struct object *parse_object(const struct object_id *oid)
{
	unsigned long size;
	enum object_type type;
	int eaten;
	const unsigned char *repl = lookup_replace_object(oid->hash);
	void *buffer;
	struct object *obj;

	obj = lookup_object(oid->hash);
	if (obj && obj->parsed)
		return obj;

	if ((obj && obj->type == OBJ_BLOB) ||
	    (!obj && has_object_file(oid) &&
	     sha1_object_info(oid->hash, NULL) == OBJ_BLOB)) {
		if (check_sha1_signature(repl, NULL, 0, NULL) < 0) {
			error("sha1 mismatch %s", oid_to_hex(oid));
			return NULL;
		}
		parse_blob_buffer(lookup_blob(oid), NULL, 0);
		return lookup_object(oid->hash);
	}

	buffer = read_sha1_file(oid->hash, &type, &size);
	if (buffer) {
		if (check_sha1_signature(repl, buffer, size, typename(type)) < 0) {
			free(buffer);
			error("sha1 mismatch %s", sha1_to_hex(repl));
			return NULL;
		}

		obj = parse_object_buffer(oid, type, size, buffer, &eaten);
		if (!eaten)
			free(buffer);
		return obj;
	}
	return NULL;
}