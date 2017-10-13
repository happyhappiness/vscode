die(_("You have not concluded your previous "
				    "notes merge (%s exists).\nPlease, use "
				    "'git notes merge --commit' or 'git notes "
				    "merge --abort' to commit/abort the "
				    "previous merge before you start a new "
				    "notes merge."), git_path("NOTES_MERGE_*"));