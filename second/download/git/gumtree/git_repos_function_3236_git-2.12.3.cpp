int for_each_reflog(each_ref_fn fn, void *cb_data)
{
	struct ref_store *refs = get_ref_store(NULL);
	struct ref_iterator *iter;

	iter = refs->be->reflog_iterator_begin(refs);

	return do_for_each_ref_iterator(iter, fn, cb_data);
}