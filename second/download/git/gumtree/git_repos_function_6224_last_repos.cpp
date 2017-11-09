static int merge_trivial(struct commit *head, struct commit_list *remoteheads)
{
	struct object_id result_tree, result_commit;
	struct commit_list *parents, **pptr = &parents;
	static struct lock_file lock;

	hold_locked_index(&lock, LOCK_DIE_ON_ERROR);
	refresh_cache(REFRESH_QUIET);
	if (active_cache_changed &&
	    write_locked_index(&the_index, &lock, COMMIT_LOCK))
		return error(_("Unable to write index."));
	rollback_lock_file(&lock);

	write_tree_trivial(&result_tree);
	printf(_("Wonderful.\n"));
	pptr = commit_list_append(head, pptr);
	pptr = commit_list_append(remoteheads->item, pptr);
	prepare_to_commit(remoteheads);
	if (commit_tree(merge_msg.buf, merge_msg.len, result_tree.hash, parents,
			result_commit.hash, NULL, sign_commit))
		die(_("failed to write commit object"));
	finish(head, remoteheads, &result_commit, "In-index merge");
	drop_save();
	return 0;
}