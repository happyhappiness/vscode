int for_each_reflog_ent(const char *refname, each_reflog_ent_fn fn,
			void *cb_data)
{
	return refs_for_each_reflog_ent(get_main_ref_store(), refname,
					fn, cb_data);
}