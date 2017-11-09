int for_each_ref_in_submodule(const char *submodule, const char *prefix,
			      each_ref_fn fn, void *cb_data)
{
	return refs_for_each_ref_in(get_submodule_ref_store(submodule),
				    prefix, fn, cb_data);
}