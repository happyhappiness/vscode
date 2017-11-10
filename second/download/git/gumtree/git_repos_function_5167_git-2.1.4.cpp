static int merge(int argc, const char **argv, const char *prefix)
{
	struct strbuf remote_ref = STRBUF_INIT, msg = STRBUF_INIT;
	unsigned char result_sha1[20];
	struct notes_tree *t;
	struct notes_merge_options o;
	int do_merge = 0, do_commit = 0, do_abort = 0;
	int verbosity = 0, result;
	const char *strategy = NULL;
	struct option options[] = {
		OPT_GROUP(N_("General options")),
		OPT__VERBOSITY(&verbosity),
		OPT_GROUP(N_("Merge options")),
		OPT_STRING('s', "strategy", &strategy, N_("strategy"),
			   N_("resolve notes conflicts using the given strategy "
			      "(manual/ours/theirs/union/cat_sort_uniq)")),
		OPT_GROUP(N_("Committing unmerged notes")),
		{ OPTION_SET_INT, 0, "commit", &do_commit, NULL,
			N_("finalize notes merge by committing unmerged notes"),
			PARSE_OPT_NOARG | PARSE_OPT_NONEG, NULL, 1},
		OPT_GROUP(N_("Aborting notes merge resolution")),
		{ OPTION_SET_INT, 0, "abort", &do_abort, NULL,
			N_("abort notes merge"),
			PARSE_OPT_NOARG | PARSE_OPT_NONEG, NULL, 1},
		OPT_END()
	};

	argc = parse_options(argc, argv, prefix, options,
			     git_notes_merge_usage, 0);

	if (strategy || do_commit + do_abort == 0)
		do_merge = 1;
	if (do_merge + do_commit + do_abort != 1) {
		error("cannot mix --commit, --abort or -s/--strategy");
		usage_with_options(git_notes_merge_usage, options);
	}

	if (do_merge && argc != 1) {
		error("Must specify a notes ref to merge");
		usage_with_options(git_notes_merge_usage, options);
	} else if (!do_merge && argc) {
		error("too many parameters");
		usage_with_options(git_notes_merge_usage, options);
	}

	init_notes_merge_options(&o);
	o.verbosity = verbosity + NOTES_MERGE_VERBOSITY_DEFAULT;

	if (do_abort)
		return merge_abort(&o);
	if (do_commit)
		return merge_commit(&o);

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
		       git_path(NOTES_MERGE_WORKTREE));
	}

	free_notes(t);
	strbuf_release(&remote_ref);
	strbuf_release(&msg);
	return result < 0; /* return non-zero on conflicts */
}