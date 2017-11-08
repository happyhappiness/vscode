int for_each_ref_in(const char *prefix, each_ref_fn fn, void *cb_data)
{
	return refs_for_each_ref_in(get_main_ref_store(), prefix, fn, cb_data);
}