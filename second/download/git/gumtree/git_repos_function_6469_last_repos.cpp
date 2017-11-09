int ref_iterator_peel(struct ref_iterator *ref_iterator,
		      struct object_id *peeled)
{
	return ref_iterator->vtable->peel(ref_iterator, peeled);
}