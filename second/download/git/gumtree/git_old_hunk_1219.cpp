	int ret;

	assert(state->msg);
	ret = run_hook_le(NULL, "applypatch-msg", am_path(state, "final-commit"), NULL);

	if (!ret) {
		free(state->msg);
		state->msg = NULL;
		if (read_commit_msg(state) < 0)
			die(_("'%s' was deleted by the applypatch-msg hook"),
				am_path(state, "final-commit"));
	}

	return ret;
