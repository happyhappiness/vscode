int refs_for_each_ref_in(struct ref_store *refs, const char *prefix,
			 each_ref_fn fn, void *cb_data)
{
	return do_for_each_ref(refs, prefix, fn, strlen(prefix), 0, cb_data);
}