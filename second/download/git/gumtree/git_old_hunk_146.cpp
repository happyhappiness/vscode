		return git_config_string(&pager_program, var, value);

	if (!strcmp(var, "core.editor"))
		return git_config_string(&editor_program, var, value);

	if (!strcmp(var, "core.commentchar")) {
		const char *comment;
		int ret = git_config_string(&comment, var, value);
		if (!ret)
			comment_line_char = comment[0];
		return ret;
	}

	if (!strcmp(var, "core.askpass"))
		return git_config_string(&askpass_program, var, value);

	if (!strcmp(var, "core.excludesfile"))
