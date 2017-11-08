static int pull_into_void(const struct object_id *merge_head,
		const struct object_id *curr_head)
{
	/*
	 * Two-way merge: we treat the index as based on an empty tree,
	 * and try to fast-forward to HEAD. This ensures we will not lose
	 * index/worktree changes that the user already made on the unborn
	 * branch.
	 */
	if (checkout_fast_forward(&empty_tree_oid, merge_head, 0))
		return 1;

	if (update_ref("initial pull", "HEAD", merge_head->hash, curr_head->hash, 0, UPDATE_REFS_DIE_ON_ERR))
		return 1;

	return 0;
}