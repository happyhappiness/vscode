	struct strbuf msg = STRBUF_INIT;

	time(&now);
	commit = alloc_commit_node();
	commit->object.parsed = 1;
	commit->date = now;
	parent_tail = &commit->parents;

	if (!resolve_ref_unsafe("HEAD", head_sha1, 1, NULL))
		die("no such ref: HEAD");

	parent_tail = append_parent(parent_tail, head_sha1);
