static int merge_ref_iterator_abort(struct ref_iterator *ref_iterator)
{
	struct merge_ref_iterator *iter =
		(struct merge_ref_iterator *)ref_iterator;
	int ok = ITER_DONE;

	if (iter->iter0) {
		if (ref_iterator_abort(iter->iter0) != ITER_DONE)
			ok = ITER_ERROR;
	}
	if (iter->iter1) {
		if (ref_iterator_abort(iter->iter1) != ITER_DONE)
			ok = ITER_ERROR;
	}
	base_ref_iterator_free(ref_iterator);
	return ok;
}