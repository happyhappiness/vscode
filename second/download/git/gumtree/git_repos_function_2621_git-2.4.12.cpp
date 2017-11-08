int for_each_remote_ref(each_ref_fn fn, void *cb_data)
{
	return for_each_ref_in("refs/remotes/", fn, cb_data);
}