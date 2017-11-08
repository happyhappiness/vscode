static int for_each_good_bisect_ref(const char *submodule, each_ref_fn fn, void *cb_data)
{
	return for_each_ref_in_submodule(submodule, "refs/bisect/good", fn, cb_data);
}