int for_each_replace_ref(each_ref_fn fn, void *cb_data)
{
	return do_for_each_ref(&ref_cache, "refs/replace/", fn, 13, 0, cb_data);
}