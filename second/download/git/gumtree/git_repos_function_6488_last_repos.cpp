int do_for_each_ref_iterator(struct ref_iterator *iter,
			     each_ref_fn fn, void *cb_data)
{
	int retval = 0, ok;
	struct ref_iterator *old_ref_iter = current_ref_iter;

	current_ref_iter = iter;
	while ((ok = ref_iterator_advance(iter)) == ITER_OK) {
		retval = fn(iter->refname, iter->oid, iter->flags, cb_data);
		if (retval) {
			/*
			 * If ref_iterator_abort() returns ITER_ERROR,
			 * we ignore that error in deference to the
			 * callback function's return value.
			 */
			ref_iterator_abort(iter);
			goto out;
		}
	}

out:
	current_ref_iter = old_ref_iter;
	if (ok == ITER_ERROR)
		return -1;
	return retval;
}