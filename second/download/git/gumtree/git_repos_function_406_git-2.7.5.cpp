int notes_cache_put(struct notes_cache *c, unsigned char key_sha1[20],
		    const char *data, size_t size)
{
	unsigned char value_sha1[20];

	if (write_sha1_file(data, size, "blob", value_sha1) < 0)
		return -1;
	return add_note(&c->tree, key_sha1, value_sha1, NULL);
}