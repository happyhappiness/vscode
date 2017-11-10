struct ref_iterator *empty_ref_iterator_begin(void)
{
	struct empty_ref_iterator *iter = xcalloc(1, sizeof(*iter));
	struct ref_iterator *ref_iterator = &iter->base;

	base_ref_iterator_init(ref_iterator, &empty_ref_iterator_vtable);
	return ref_iterator;
}