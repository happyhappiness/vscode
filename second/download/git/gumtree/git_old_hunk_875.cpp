					"and try again.\n")
				: _("\n"
					"It looks like you may be committing a cherry-pick.\n"
					"If this is not correct, please remove the file\n"
					"	%s\n"
					"and try again.\n"),
				git_path(whence == FROM_MERGE
					 ? "MERGE_HEAD"
					 : "CHERRY_PICK_HEAD"));
		}

		fprintf(s->fp, "\n");
		if (cleanup_mode == CLEANUP_ALL)
			status_printf(s, GIT_COLOR_NORMAL,
				_("Please enter the commit message for your changes."
