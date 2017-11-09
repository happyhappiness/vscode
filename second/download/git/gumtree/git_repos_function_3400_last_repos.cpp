int refs_for_each_remote_ref(struct ref_store *refs, each_ref_fn fn, void *cb_data)
{
	return refs_for_each_ref_in(refs, "refs/remotes/", fn, cb_data);
}