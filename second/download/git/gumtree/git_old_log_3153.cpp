printf("Automatic notes merge failed. Fix conflicts in %s and "
		       "commit the result with 'git notes merge --commit', or "
		       "abort the merge with 'git notes merge --abort'.\n",
		       git_path(NOTES_MERGE_WORKTREE));