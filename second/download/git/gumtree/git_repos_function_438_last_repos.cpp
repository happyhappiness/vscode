int notes_cache_put(struct notes_cache *c, struct object_id *key_oid,
		    const char *data, size_t size)
{
	struct object_id value_oid;

	if (write_sha1_file(data, size, "blob", value_oid.hash) < 0)
		return -1;
	return add_note(&c->tree, key_oid, &value_oid, NULL);
}