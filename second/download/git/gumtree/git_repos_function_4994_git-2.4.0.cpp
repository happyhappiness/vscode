static const void *anonymize_mem(struct hashmap *map,
				 void *(*generate)(const void *, size_t *),
				 const void *orig, size_t *len)
{
	struct anonymized_entry key, *ret;

	if (!map->cmpfn)
		hashmap_init(map, anonymized_entry_cmp, 0);

	hashmap_entry_init(&key, memhash(orig, *len));
	key.orig = orig;
	key.orig_len = *len;
	ret = hashmap_get(map, &key, NULL);

	if (!ret) {
		ret = xmalloc(sizeof(*ret));
		hashmap_entry_init(&ret->hash, key.hash.hash);
		ret->orig = xstrdup(orig);
		ret->orig_len = *len;
		ret->anon = generate(orig, len);
		ret->anon_len = *len;
		hashmap_put(map, ret);
	}

	*len = ret->anon_len;
	return ret->anon;
}