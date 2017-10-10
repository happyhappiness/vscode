
	parse_commit_or_die(commit);
	commit_buffer = get_commit_buffer(commit, NULL);
	author = strstr(commit_buffer, "\nauthor ");
	if (!author)
		die ("Could not find author in commit %s",
		     oid_to_hex(&commit->object.oid));
	author++;
	author_end = strchrnul(author, '\n');
	committer = strstr(author_end, "\ncommitter ");
	if (!committer)
		die ("Could not find committer in commit %s",
		     oid_to_hex(&commit->object.oid));
	committer++;
	committer_end = strchrnul(committer, '\n');
	message = strstr(committer_end, "\n\n");
	encoding = find_encoding(committer_end, message);
	if (message)
		message += 2;

	if (commit->parents &&
	    get_object_mark(&commit->parents->item->object) != 0 &&
	    !full_tree) {
		parse_commit_or_die(commit->parents->item);
		diff_tree_sha1(commit->parents->item->tree->object.oid.hash,
			       commit->tree->object.oid.hash, "", &rev->diffopt);
	}
	else
		diff_root_tree_sha1(commit->tree->object.oid.hash,
				    "", &rev->diffopt);

	/* Export the referenced blobs, and remember the marks. */
	for (i = 0; i < diff_queued_diff.nr; i++)
		if (!S_ISGITLINK(diff_queued_diff.queue[i]->two->mode))
			export_blob(diff_queued_diff.queue[i]->two->sha1);
