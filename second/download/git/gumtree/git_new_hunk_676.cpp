	if (!default_refs) {
		fprintf(stderr, "notice: No default references\n");
		show_unreachable = 0;
	}
}

static struct object *parse_loose_object(const unsigned char *sha1,
					 const char *path)
{
	struct object *obj;
	void *contents;
	enum object_type type;
	unsigned long size;
	int eaten;

	if (read_loose_object(path, sha1, &type, &size, &contents) < 0)
		return NULL;

	if (!contents && type != OBJ_BLOB)
		die("BUG: read_loose_object streamed a non-blob");

	obj = parse_object_buffer(sha1, type, size, contents, &eaten);

	if (!eaten)
		free(contents);
	return obj;
}

static int fsck_loose(const unsigned char *sha1, const char *path, void *data)
{
	struct object *obj = parse_loose_object(sha1, path);

	if (!obj) {
		errors_found |= ERROR_OBJECT;
		error("%s: object corrupt or missing: %s",
		      sha1_to_hex(sha1), path);
		return 0; /* keep checking other objects */
	}

	obj->flags = HAS_OBJ;
	if (fsck_obj(obj))
		errors_found |= ERROR_OBJECT;
	return 0;
}

static int fsck_cruft(const char *basename, const char *path, void *data)
{
