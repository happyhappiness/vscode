int for_each_ref_in(const char *prefix, each_ref_fn fn, void *cb_data)
{
	return do_for_each_ref(&ref_cache, prefix, fn, strlen(prefix), 0, cb_data);
}