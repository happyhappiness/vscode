		free(ref);
	}

	if (get_sha1(name, oid.hash))
		die("Not a valid object name");

	commit = lookup_commit_reference_gently(&oid, 1);
	if (commit) {
		commit_sha1 = commit->object.oid.hash;
		archive_time = commit->date;
	} else {
		commit_sha1 = NULL;
		archive_time = time(NULL);
	}

	tree = parse_tree_indirect(&oid);
	if (tree == NULL)
		die("not a tree object");

	if (prefix) {
		struct object_id tree_oid;
		unsigned int mode;
