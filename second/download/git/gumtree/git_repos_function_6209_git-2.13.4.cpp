static int add_loose_object(const struct object_id *oid, const char *path,
			    void *data)
{
	enum object_type type = sha1_object_info(oid->hash, NULL);

	if (type < 0) {
		warning("loose object at %s could not be examined", path);
		return 0;
	}

	add_object_entry(oid->hash, type, "", 0);
	return 0;
}