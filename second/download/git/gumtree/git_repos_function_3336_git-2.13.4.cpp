int for_each_rawref(each_ref_fn fn, void *cb_data)
{
	return refs_for_each_rawref(get_main_ref_store(), fn, cb_data);
}