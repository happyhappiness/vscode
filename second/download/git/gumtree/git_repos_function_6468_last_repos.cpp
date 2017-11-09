int ref_iterator_advance(struct ref_iterator *ref_iterator)
{
	return ref_iterator->vtable->advance(ref_iterator);
}