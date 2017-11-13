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