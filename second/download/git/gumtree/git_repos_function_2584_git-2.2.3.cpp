int for_each_branch_ref(each_ref_fn fn, void *cb_data)
{
	return for_each_ref_in("refs/heads/", fn, cb_data);
}