static void *insert_decoration(struct decoration *n, const struct object *base, void *decoration)
{
	int size = n->size;
	struct object_decoration *hash = n->hash;
	unsigned int j = hash_obj(base, size);

	while (hash[j].base) {
		if (hash[j].base == base) {
			void *old = hash[j].decoration;
			hash[j].decoration = decoration;
			return old;
		}
		if (++j >= size)
			j = 0;
	}
	hash[j].base = base;
	hash[j].decoration = decoration;
	n->nr++;
	return NULL;
}