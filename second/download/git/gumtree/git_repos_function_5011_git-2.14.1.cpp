static int get_octopus_merge_base(struct object_id *merge_base,
		const struct object_id *curr_head,
		const struct object_id *merge_head,
		const struct object_id *fork_point)
{
	struct commit_list *revs = NULL, *result;

	commit_list_insert(lookup_commit_reference(curr_head), &revs);
	commit_list_insert(lookup_commit_reference(merge_head), &revs);
	if (!is_null_oid(fork_point))
		commit_list_insert(lookup_commit_reference(fork_point), &revs);

	result = reduce_heads(get_octopus_merge_bases(revs));
	free_commit_list(revs);
	if (!result)
		return 1;

	oidcpy(merge_base, &result->item->object.oid);
	return 0;
}