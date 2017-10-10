	if (!default_refs) {
		fprintf(stderr, "notice: No default references\n");
		show_unreachable = 0;
	}
}

static struct object *parse_loose_object(const struct object_id *oid,
					 const char *path)
{
	struct object *obj;
	void *contents;
	enum object_type type;
	unsigned long size;
	int eaten;

	if (read_loose_object(path, oid->hash, &type, &size, &contents) < 0)
		return NULL;

	if (!contents && type != OBJ_BLOB)
		die("BUG: read_loose_object streamed a non-blob");

	obj = parse_object_buffer(oid->hash, type, size, contents, &eaten);

	if (!eaten)
		free(contents);
	return obj;
}

static int fsck_loose(const struct object_id *oid, const char *path, void *data)
{
	struct object *obj = parse_loose_object(oid, path);

	if (!obj) {
		errors_found |= ERROR_OBJECT;
		error("%s: object corrupt or missing: %s",
		      oid_to_hex(oid), path);
		return 0; /* keep checking other objects */
	}

	obj->flags = HAS_OBJ;
	if (fsck_obj(obj))
		errors_found |= ERROR_OBJECT;
