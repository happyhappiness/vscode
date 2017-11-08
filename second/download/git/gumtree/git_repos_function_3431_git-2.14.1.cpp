static int do_for_each_ref(struct ref_store *refs, const char *prefix,
			   each_ref_fn fn, int trim, int flags, void *cb_data)
{
	struct ref_iterator *iter;

	if (!refs)
		return 0;

	iter = refs_ref_iterator_begin(refs, prefix, trim, flags);

	return do_for_each_ref_iterator(iter, fn, cb_data);
}