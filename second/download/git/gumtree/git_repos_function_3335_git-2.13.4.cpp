int refs_for_each_rawref(struct ref_store *refs, each_ref_fn fn, void *cb_data)
{
	return do_for_each_ref(refs, "", fn, 0,
			       DO_FOR_EACH_INCLUDE_BROKEN, cb_data);
}