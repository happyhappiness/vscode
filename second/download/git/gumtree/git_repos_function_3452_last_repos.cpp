int for_each_fullref_in_submodule(const char *submodule, const char *prefix,
				  each_ref_fn fn, void *cb_data,
				  unsigned int broken)
{
	unsigned int flag = 0;

	if (broken)
		flag = DO_FOR_EACH_INCLUDE_BROKEN;
	return do_for_each_ref(get_submodule_ref_store(submodule),
			       prefix, fn, 0, flag, cb_data);
}