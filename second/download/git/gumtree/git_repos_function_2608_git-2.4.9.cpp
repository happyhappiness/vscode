int head_ref_submodule(const char *submodule, each_ref_fn fn, void *cb_data)
{
	return do_head_ref(submodule, fn, cb_data);
}