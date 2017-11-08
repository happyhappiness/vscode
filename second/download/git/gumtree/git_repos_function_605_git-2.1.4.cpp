struct commit_list *get_merge_bases(struct commit *one, struct commit *two,
				    int cleanup)
{
	return get_merge_bases_many(one, 1, &two, cleanup);
}