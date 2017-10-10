
	o.local_ref = default_notes_ref();
	strbuf_addstr(&remote_ref, argv[0]);
	expand_notes_ref(&remote_ref);
	o.remote_ref = remote_ref.buf;

	if (strategy) {
		if (!strcmp(strategy, "manual"))
			o.strategy = NOTES_MERGE_RESOLVE_MANUAL;
		else if (!strcmp(strategy, "ours"))
			o.strategy = NOTES_MERGE_RESOLVE_OURS;
		else if (!strcmp(strategy, "theirs"))
			o.strategy = NOTES_MERGE_RESOLVE_THEIRS;
		else if (!strcmp(strategy, "union"))
			o.strategy = NOTES_MERGE_RESOLVE_UNION;
		else if (!strcmp(strategy, "cat_sort_uniq"))
			o.strategy = NOTES_MERGE_RESOLVE_CAT_SORT_UNIQ;
		else {
			error("Unknown -s/--strategy: %s", strategy);
			usage_with_options(git_notes_merge_usage, options);
		}
	}

	t = init_notes_check("merge");

	strbuf_addf(&msg, "notes: Merged notes from %s into %s",
		    remote_ref.buf, default_notes_ref());
	strbuf_add(&(o.commit_msg), msg.buf + 7, msg.len - 7); /* skip "notes: " */

	result = notes_merge(&o, t, result_sha1);

	if (result >= 0) /* Merge resulted (trivially) in result_sha1 */
		/* Update default notes ref with new commit */
		update_ref(msg.buf, default_notes_ref(), result_sha1, NULL,
			   0, UPDATE_REFS_DIE_ON_ERR);
	else { /* Merge has unresolved conflicts */
		/* Update .git/NOTES_MERGE_PARTIAL with partial merge result */
		update_ref(msg.buf, "NOTES_MERGE_PARTIAL", result_sha1, NULL,
			   0, UPDATE_REFS_DIE_ON_ERR);
		/* Store ref-to-be-updated into .git/NOTES_MERGE_REF */
		if (create_symref("NOTES_MERGE_REF", default_notes_ref(), NULL))
			die("Failed to store link to current notes ref (%s)",
			    default_notes_ref());
		printf("Automatic notes merge failed. Fix conflicts in %s and "
		       "commit the result with 'git notes merge --commit', or "
		       "abort the merge with 'git notes merge --abort'.\n",
