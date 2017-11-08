static void *get_obj(const unsigned char *sha1, struct object **obj, unsigned long *sz, int *eaten)
{
	enum object_type type;
	void *buf = read_sha1_file(sha1, &type, sz);

	if (buf)
		*obj = parse_object_buffer(sha1, type, *sz, buf, eaten);
	else
		*obj = NULL;
	return buf;
}