static void cache_one_alternate(const char *refname,
				const struct object_id *oid,
				void *vcache)
{
	struct alternate_object_cache *cache = vcache;
	struct object *obj = parse_object(oid);

	if (!obj || (obj->flags & ALTERNATE))
		return;

	obj->flags |= ALTERNATE;
	ALLOC_GROW(cache->items, cache->nr + 1, cache->alloc);
	cache->items[cache->nr++] = obj;
}