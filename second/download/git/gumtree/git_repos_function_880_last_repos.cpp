int for_each_commit_graft(each_commit_graft_fn fn, void *cb_data)
{
	int i, ret;
	for (i = ret = 0; i < commit_graft_nr && !ret; i++)
		ret = fn(commit_graft[i], cb_data);
	return ret;
}