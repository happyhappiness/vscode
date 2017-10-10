	time(&now);
	commit = alloc_commit_node();
	commit->object.parsed = 1;
	commit->date = now;
	parent_tail = &commit->parents;

	if (!resolve_ref_unsafe("HEAD", RESOLVE_REF_READING, head_sha1, NULL))
		die("no such ref: HEAD");

	parent_tail = append_parent(parent_tail, head_sha1);
	append_merge_parents(parent_tail);
	verify_working_tree_path(commit, path);

	origin = make_origin(commit, path);

	ident = fmt_ident("Not Committed Yet", "not.committed.yet", NULL, 0);
