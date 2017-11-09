static int empty_ref_iterator_abort(struct ref_iterator *ref_iterator)
{
	base_ref_iterator_free(ref_iterator);
	return ITER_DONE;
}