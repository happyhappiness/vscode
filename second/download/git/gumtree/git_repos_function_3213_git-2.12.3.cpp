static int do_for_each_ref(const char *submodule, const char *prefix,
			   each_ref_fn fn, int trim, int flags, void *cb_data)
{
	struct ref_store *refs = get_ref_store(submodule);
	struct ref_iterator *iter;

	if (!refs)
		return 0;

	iter = refs->be->iterator_begin(refs, prefix, flags);
	iter = prefix_ref_iterator_begin(iter, prefix, trim);

	return do_for_each_ref_iterator(iter, fn, cb_data);
}