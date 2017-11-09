static int fsck_loose(const struct object_id *oid, const char *path, void *data)
{
	struct object *obj = parse_loose_object(oid, path);

	if (!obj) {
		errors_found |= ERROR_OBJECT;
		error("%s: object corrupt or missing: %s",
		      oid_to_hex(oid), path);
		return 0; /* keep checking other objects */
	}

	obj->flags &= ~(REACHABLE | SEEN);
	obj->flags |= HAS_OBJ;
	if (fsck_obj(obj))
		errors_found |= ERROR_OBJECT;
	return 0;
}