int branch_has_merge_config(struct branch *branch)
{
	return branch && !!branch->merge;
}