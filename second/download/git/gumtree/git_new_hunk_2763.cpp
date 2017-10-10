
	if (get_sha1(name, oid.hash))
		die("Not a valid object name");

	commit = lookup_commit_reference_gently(oid.hash, 1);
	if (commit) {
		commit_sha1 = commit->object.oid.hash;
		archive_time = commit->date;
	} else {
		commit_sha1 = NULL;
		archive_time = time(NULL);
	}

