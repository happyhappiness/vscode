static int get_octopus_merge_base(unsigned char *merge_base,
		const unsigned char *curr_head,
		const unsigned char *merge_head,
		const unsigned char *fork_point)
{
	struct commit_list *revs = NULL, *result;

	commit_list_insert(lookup_commit_reference(curr_head), &revs);
	commit_list_insert(lookup_commit_reference(merge_head), &revs);
	if (!is_null_sha1(fork_point))
		commit_list_insert(lookup_commit_reference(fork_point), &revs);

	result = reduce_heads(get_octopus_merge_bases(revs));
	free_commit_list(revs);
	if (!result)
		return 1;

	hashcpy(merge_base, result->item->object.oid.hash);
	return 0;
}