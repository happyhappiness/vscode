int refs_for_each_reflog_ent(struct ref_store *refs, const char *refname,
			     each_reflog_ent_fn fn, void *cb_data)
{
	return refs->be->for_each_reflog_ent(refs, refname, fn, cb_data);
}