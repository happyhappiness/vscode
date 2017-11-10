int head_ref(each_ref_fn fn, void *cb_data)
{
	return head_ref_submodule(NULL, fn, cb_data);
}