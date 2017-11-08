static int fsck_obj_buffer(const unsigned char *sha1, enum object_type type,
			   unsigned long size, void *buffer, int *eaten)
{
	/*
	 * Note, buffer may be NULL if type is OBJ_BLOB. See
	 * verify_packfile(), data_valid variable for details.
	 */
	struct object *obj;
	obj = parse_object_buffer(sha1, type, size, buffer, eaten);
	if (!obj) {
		errors_found |= ERROR_OBJECT;
		return error("%s: object corrupt or missing", sha1_to_hex(sha1));
	}
	obj->flags = HAS_OBJ;
	return fsck_obj(obj);
}