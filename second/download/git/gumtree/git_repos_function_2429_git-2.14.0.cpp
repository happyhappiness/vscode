static void initialize_ll_merge(void)
{
	if (ll_user_merge_tail)
		return;
	ll_user_merge_tail = &ll_user_merge;
	git_config(read_merge_config, NULL);
}