char *notes_cache_get(struct notes_cache *c, unsigned char key_sha1[20],
		      size_t *outsize)
{
	const unsigned char *value_sha1;
	enum object_type type;
	char *value;
	unsigned long size;

	value_sha1 = get_note(&c->tree, key_sha1);
	if (!value_sha1)
		return NULL;
	value = read_sha1_file(value_sha1, &type, &size);

	*outsize = size;
	return value;
}