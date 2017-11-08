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

	obj = parse_object_buffer(oid, type, size, contents, &eaten);

	if (!eaten)
		free(contents);
	return obj;
}