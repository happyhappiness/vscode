static int empty_ref_iterator_advance(struct ref_iterator *ref_iterator)
{
	return ref_iterator_abort(ref_iterator);
}