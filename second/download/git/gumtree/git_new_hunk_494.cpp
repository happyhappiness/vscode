		 * Must establish NOTES_MERGE_WORKTREE.
		 * Abort if NOTES_MERGE_WORKTREE already exists
		 */
		if (file_exists(git_path(NOTES_MERGE_WORKTREE)) &&
		    !is_empty_dir(git_path(NOTES_MERGE_WORKTREE))) {
			if (advice_resolve_conflict)
				die(_("You have not concluded your previous "
				    "notes merge (%s exists).\nPlease, use "
				    "'git notes merge --commit' or 'git notes "
				    "merge --abort' to commit/abort the "
				    "previous merge before you start a new "
				    "notes merge."), git_path("NOTES_MERGE_*"));
			else
				die(_("You have not concluded your notes merge "
				    "(%s exists)."), git_path("NOTES_MERGE_*"));
		}

		if (safe_create_leading_directories_const(git_path(
				NOTES_MERGE_WORKTREE "/.test")))
			die_errno("unable to create directory %s",
				  git_path(NOTES_MERGE_WORKTREE));
