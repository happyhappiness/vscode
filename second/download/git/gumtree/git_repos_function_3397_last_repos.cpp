int refs_for_each_branch_ref(struct ref_store *refs, each_ref_fn fn, void *cb_data)
{
	return refs_for_each_ref_in(refs, "refs/heads/", fn, cb_data);
}