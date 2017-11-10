int for_each_branch_ref_submodule(const char *submodule, each_ref_fn fn, void *cb_data)
{
	return refs_for_each_branch_ref(get_submodule_ref_store(submodule),
					fn, cb_data);
}