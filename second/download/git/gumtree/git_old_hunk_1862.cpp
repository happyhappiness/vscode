	 */
	revs->tag_objects = 1;
	revs->blob_objects = 1;
	revs->tree_objects = 1;

	/* Add all refs from the index file */
	add_cache_refs(revs);

	/* Add all external refs */
	for_each_ref(add_one_ref, revs);

	/* detached HEAD is not included in the list above */
	head_ref(add_one_ref, revs);

	/* Add all reflog info */
	if (mark_reflog)
		for_each_reflog(add_one_reflog, revs);

	cp.progress = progress;
	cp.count = 0;

	/*
	 * Set up the revision walk - this will move all commits
	 * from the pending list to the commit walking list.
	 */
	if (prepare_revision_walk(revs))
		die("revision walk setup failed");
	walk_commit_list(revs, &cp);
	display_progress(cp.progress, cp.count);
}
