static int files_ref_iterator_abort(struct ref_iterator *ref_iterator)
{
	struct files_ref_iterator *iter =
		(struct files_ref_iterator *)ref_iterator;
	int ok = ITER_DONE;

	if (iter->iter0)
		ok = ref_iterator_abort(iter->iter0);

	release_packed_ref_cache(iter->packed_ref_cache);
	base_ref_iterator_free(ref_iterator);
	return ok;
}