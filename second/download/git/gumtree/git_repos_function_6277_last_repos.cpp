static int type_size_sort(const void *_a, const void *_b)
{
	const struct object_entry *a = *(struct object_entry **)_a;
	const struct object_entry *b = *(struct object_entry **)_b;

	if (a->type > b->type)
		return -1;
	if (a->type < b->type)
		return 1;
	if (a->hash > b->hash)
		return -1;
	if (a->hash < b->hash)
		return 1;
	if (a->preferred_base > b->preferred_base)
		return -1;
	if (a->preferred_base < b->preferred_base)
		return 1;
	if (a->size > b->size)
		return -1;
	if (a->size < b->size)
		return 1;
	return a < b ? -1 : (a > b);  /* newest first */
}