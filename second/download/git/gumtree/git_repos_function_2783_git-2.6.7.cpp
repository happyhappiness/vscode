int for_each_tag_ref(each_ref_fn fn, void *cb_data)
{
	return for_each_ref_in("refs/tags/", fn, cb_data);
}