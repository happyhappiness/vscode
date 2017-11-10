struct commit_list *get_merge_bases(struct commit *one, struct commit *two)
{
	return get_merge_bases_many_0(one, 1, &two, 1);
}