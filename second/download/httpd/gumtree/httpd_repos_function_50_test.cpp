struct commit_list *get_merge_bases_many(struct commit *one,
					 int n,
					 struct commit **twos)
{
	return get_merge_bases_many_0(one, n, twos, 1);
}