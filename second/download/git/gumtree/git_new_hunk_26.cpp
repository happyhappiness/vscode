		}

		if (!use_stdout &&
		    reopen_stdout(rev.numbered_files ? NULL : commit, NULL, &rev, quiet))
			die(_("Failed to create output files"));
		shown = log_tree_commit(&rev, commit);
		free_commit_buffer(commit);

		/* We put one extra blank line between formatted
		 * patches and this flag is used by log-tree code
		 * to see if it needs to emit a LF before showing
		 * the log; when using one file per patch, we do
		 * not want the extra blank line.
