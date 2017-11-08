int for_each_rawref(each_ref_fn fn, void *cb_data)
{
	return do_for_each_ref(&ref_cache, "", fn, 0,
			       DO_FOR_EACH_INCLUDE_BROKEN, cb_data);
}