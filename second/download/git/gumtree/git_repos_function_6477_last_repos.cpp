int is_empty_ref_iterator(struct ref_iterator *ref_iterator)
{
	return ref_iterator->vtable == &empty_ref_iterator_vtable;
}