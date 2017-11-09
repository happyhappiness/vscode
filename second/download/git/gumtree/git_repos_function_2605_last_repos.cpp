static void grow_decoration(struct decoration *n)
{
	int i;
	int old_size = n->size;
	struct object_decoration *old_hash = n->hash;

	n->size = (old_size + 1000) * 3 / 2;
	n->hash = xcalloc(n->size, sizeof(struct object_decoration));
	n->nr = 0;

	for (i = 0; i < old_size; i++) {
		const struct object *base = old_hash[i].base;
		void *decoration = old_hash[i].decoration;

		if (!decoration)
			continue;
		insert_decoration(n, base, decoration);
	}
	free(old_hash);
}