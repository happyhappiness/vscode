static void check_notes_merge_worktree(struct notes_merge_options *o)
{
	if (!o->has_worktree) {
		/*
		 * Must establish NOTES_MERGE_WORKTREE.
		 * Abort if NOTES_MERGE_WORKTREE already exists
		 */
		if (file_exists(git_path(NOTES_MERGE_WORKTREE)) &&
		    !is_empty_dir(git_path(NOTES_MERGE_WORKTREE))) {
			if (advice_resolve_conflict)
				die("You have not concluded your previous "
				    "notes merge (%s exists).\nPlease, use "
				    "'git notes merge --commit' or 'git notes "
				    "merge --abort' to commit/abort the "
				    "previous merge before you start a new "
				    "notes merge.", git_path("NOTES_MERGE_*"));
			else
				die("You have not concluded your notes merge "
				    "(%s exists).", git_path("NOTES_MERGE_*"));
		}

		if (safe_create_leading_directories_const(git_path(
				NOTES_MERGE_WORKTREE "/.test")))
			die_errno("unable to create directory %s",
				  git_path(NOTES_MERGE_WORKTREE));
		o->has_worktree = 1;
	} else if (!file_exists(git_path(NOTES_MERGE_WORKTREE)))
		/* NOTES_MERGE_WORKTREE should already be established */
		die("missing '%s'. This should not happen",
		    git_path(NOTES_MERGE_WORKTREE));
}