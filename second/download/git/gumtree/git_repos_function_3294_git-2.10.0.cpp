static void *pop_item(struct mergesort_sublist *l,
		      void *(*get_next_fn)(const void *))
{
	void *p = l->ptr;
	l->ptr = get_next_fn(l->ptr);
	l->len = l->ptr ? (l->len - 1) : 0;
	return p;
}