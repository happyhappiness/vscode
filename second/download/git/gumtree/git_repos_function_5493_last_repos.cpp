static const char *printable_type(struct object *obj)
{
	const char *ret;

	if (obj->type == OBJ_NONE) {
		enum object_type type = sha1_object_info(obj->oid.hash, NULL);
		if (type > 0)
			object_as_type(obj, type, 0);
	}

	ret = typename(obj->type);
	if (!ret)
		ret = "unknown";

	return ret;
}