int refs_for_each_reflog_ent_reverse(struct ref_store *refs,
				     const char *refname,
				     each_reflog_ent_fn fn,
				     void *cb_data)
{
	return refs->be->for_each_reflog_ent_reverse(refs, refname,
						     fn, cb_data);
}