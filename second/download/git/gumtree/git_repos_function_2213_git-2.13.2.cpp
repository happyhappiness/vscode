static const struct git_attr *git_attr_internal(const char *name, int namelen)
{
	struct git_attr *a;

	if (!attr_name_valid(name, namelen))
		return NULL;

	hashmap_lock(&g_attr_hashmap);

	a = attr_hashmap_get(&g_attr_hashmap, name, namelen);

	if (!a) {
		FLEX_ALLOC_MEM(a, name, name, namelen);
		a->attr_nr = g_attr_hashmap.map.size;

		attr_hashmap_add(&g_attr_hashmap, a->name, namelen, a);
		assert(a->attr_nr == (g_attr_hashmap.map.size - 1));
	}

	hashmap_unlock(&g_attr_hashmap);

	return a;
}