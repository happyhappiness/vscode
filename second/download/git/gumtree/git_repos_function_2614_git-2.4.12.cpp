int for_each_ref_submodule(const char *submodule, each_ref_fn fn, void *cb_data)
{
	return do_for_each_ref(get_ref_cache(submodule), "", fn, 0, 0, cb_data);
}