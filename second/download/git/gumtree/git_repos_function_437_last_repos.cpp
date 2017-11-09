char *notes_cache_get(struct notes_cache *c, struct object_id *key_oid,
		      size_t *outsize)
{
	const struct object_id *value_oid;
	enum object_type type;
	char *value;
	unsigned long size;

	value_oid = get_note(&c->tree, key_oid);
	if (!value_oid)
		return NULL;
	value = read_sha1_file(value_oid->hash, &type, &size);

	*outsize = size;
	return value;
}