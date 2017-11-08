static void *get_obj(const struct object_id *oid, struct object **obj, unsigned long *sz, int *eaten)
{
	enum object_type type;
	void *buf = read_sha1_file(oid->hash, &type, sz);

	if (buf)
		*obj = parse_object_buffer(oid, type, *sz, buf, eaten);
	else
		*obj = NULL;
	return buf;
}