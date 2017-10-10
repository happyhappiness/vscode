	else if (!(partial = lookup_commit_reference(sha1)))
		die("Could not find commit from NOTES_MERGE_PARTIAL.");
	else if (parse_commit(partial))
		die("Could not parse commit from NOTES_MERGE_PARTIAL.");

	if (partial->parents)
		hashcpy(parent_sha1, partial->parents->item->object.sha1);
	else
		hashclr(parent_sha1);

	t = xcalloc(1, sizeof(struct notes_tree));
	init_notes(t, "NOTES_MERGE_PARTIAL", combine_notes_overwrite, 0);

