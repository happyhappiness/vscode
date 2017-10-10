
	if (run_commit_hook(use_editor, index_file, "prepare-commit-msg",
			    git_path_commit_editmsg(), hook_arg1, hook_arg2, NULL))
		return 0;

	if (use_editor) {
		char index[PATH_MAX];
		const char *env[2] = { NULL };
		env[0] =  index;
		snprintf(index, sizeof(index), "GIT_INDEX_FILE=%s", index_file);
		if (launch_editor(git_path_commit_editmsg(), NULL, env)) {
			fprintf(stderr,
			_("Please supply the message using either -m or -F option.\n"));
			exit(1);
		}
	}

	if (!no_verify &&
	    run_commit_hook(use_editor, index_file, "commit-msg", git_path_commit_editmsg(), NULL)) {
		return 0;
	}
