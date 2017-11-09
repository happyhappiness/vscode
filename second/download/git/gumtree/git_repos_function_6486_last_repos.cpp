static int prefix_ref_iterator_abort(struct ref_iterator *ref_iterator)
{
	struct prefix_ref_iterator *iter =
		(struct prefix_ref_iterator *)ref_iterator;
	int ok = ITER_DONE;

	if (iter->iter0)
		ok = ref_iterator_abort(iter->iter0);
	free(iter->prefix);
	base_ref_iterator_free(ref_iterator);
	return ok;
}