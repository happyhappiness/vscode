int for_each_ref(each_ref_fn fn, void *cb_data)
{
	return do_for_each_ref(NULL, "", fn, 0, 0, cb_data);
}