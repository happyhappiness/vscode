static int do_for_each_ref(const char *submodule, const char *prefix,
			   each_ref_fn fn, int trim, int flags, void *cb_data)
{
	struct ref_iterator *iter;

	iter = files_ref_iterator_begin(submodule, prefix, flags);
	iter = prefix_ref_iterator_begin(iter, prefix, trim);

	return do_for_each_ref_iterator(iter, fn, cb_data);
}