int for_each_reflog_ent(const char *refname, each_reflog_ent_fn fn,
			void *cb_data)
{
	struct ref_store *refs = get_ref_store(NULL);

	return refs->be->for_each_reflog_ent(refs, refname, fn, cb_data);
}