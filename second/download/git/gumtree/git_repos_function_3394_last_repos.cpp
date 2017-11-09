int refs_for_each_tag_ref(struct ref_store *refs, each_ref_fn fn, void *cb_data)
{
	return refs_for_each_ref_in(refs, "refs/tags/", fn, cb_data);
}