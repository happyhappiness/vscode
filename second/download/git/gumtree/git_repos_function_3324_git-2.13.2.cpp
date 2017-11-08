int refs_for_each_ref(struct ref_store *refs, each_ref_fn fn, void *cb_data)
{
	return do_for_each_ref(refs, "", fn, 0, 0, cb_data);
}