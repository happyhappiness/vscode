int ref_iterator_abort(struct ref_iterator *ref_iterator)
{
	return ref_iterator->vtable->abort(ref_iterator);
}