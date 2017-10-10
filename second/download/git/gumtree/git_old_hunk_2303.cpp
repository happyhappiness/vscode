				    "notes merge.", git_path("NOTES_MERGE_*"));
			else
				die("You have not concluded your notes merge "
				    "(%s exists).", git_path("NOTES_MERGE_*"));
		}

		if (safe_create_leading_directories(git_path(
				NOTES_MERGE_WORKTREE "/.test")))
			die_errno("unable to create directory %s",
				  git_path(NOTES_MERGE_WORKTREE));
		o->has_worktree = 1;
	} else if (!file_exists(git_path(NOTES_MERGE_WORKTREE)))
		/* NOTES_MERGE_WORKTREE should already be established */
