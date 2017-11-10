void *lookup_decoration(struct decoration *n, const struct object *obj)
{
	unsigned int j;

	/* nothing to lookup */
	if (!n->size)
		return NULL;
	j = hash_obj(obj, n->size);
	for (;;) {
		struct object_decoration *ref = n->hash + j;
		if (ref->base == obj)
			return ref->decoration;
		if (!ref->base)
			return NULL;
		if (++j == n->size)
			j = 0;
	}
}