	return fsck_obj(obj);
}

static int fsck_obj_buffer(const unsigned char *sha1, enum object_type type,
			   unsigned long size, void *buffer, int *eaten)
{
	struct object *obj;
	obj = parse_object_buffer(sha1, type, size, buffer, eaten);
	if (!obj) {
		errors_found |= ERROR_OBJECT;
		return error("%s: object corrupt or missing", sha1_to_hex(sha1));
	}
