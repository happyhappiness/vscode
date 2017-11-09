static struct cached_object *find_cached_object(const unsigned char *sha1)
{
	int i;
	struct cached_object *co = cached_objects;

	for (i = 0; i < cached_object_nr; i++, co++) {
		if (!hashcmp(co->sha1, sha1))
			return co;
	}
	if (!hashcmp(sha1, empty_tree.sha1))
		return &empty_tree;
	return NULL;
}