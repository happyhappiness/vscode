static int add_loose_object(const unsigned char *sha1, const char *path,
			    void *data)
{
	enum object_type type = sha1_object_info(sha1, NULL);

	if (type < 0) {
		warning("loose object at %s could not be examined", path);
		return 0;
	}

	add_object_entry(sha1, type, "", 0);
	return 0;
}