int do_for_each_ref(const char *submodule, const char *base,
		    each_ref_fn fn, int trim, int flags, void *cb_data)
{
	struct ref_entry_cb data;
	struct ref_cache *refs;

	refs = get_ref_cache(submodule);
	data.base = base;
	data.trim = trim;
	data.flags = flags;
	data.fn = fn;
	data.cb_data = cb_data;

	if (ref_paranoia < 0)
		ref_paranoia = git_env_bool("GIT_REF_PARANOIA", 0);
	if (ref_paranoia)
		data.flags |= DO_FOR_EACH_INCLUDE_BROKEN;

	return do_for_each_entry(refs, base, do_one_ref, &data);
}