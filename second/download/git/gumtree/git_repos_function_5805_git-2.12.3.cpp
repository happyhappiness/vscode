int cmd_difftool(int argc, const char **argv, const char *prefix)
{
	int use_gui_tool = 0, dir_diff = 0, prompt = -1, symlinks = 0,
	    tool_help = 0;
	static char *difftool_cmd = NULL, *extcmd = NULL;
	struct option builtin_difftool_options[] = {
		OPT_BOOL('g', "gui", &use_gui_tool,
			 N_("use `diff.guitool` instead of `diff.tool`")),
		OPT_BOOL('d', "dir-diff", &dir_diff,
			 N_("perform a full-directory diff")),
		{ OPTION_SET_INT, 'y', "no-prompt", &prompt, NULL,
			N_("do not prompt before launching a diff tool"),
			PARSE_OPT_NOARG | PARSE_OPT_NONEG, NULL, 0},
		{ OPTION_SET_INT, 0, "prompt", &prompt, NULL, NULL,
			PARSE_OPT_NOARG | PARSE_OPT_NONEG | PARSE_OPT_HIDDEN,
			NULL, 1 },
		OPT_BOOL(0, "symlinks", &symlinks,
			 N_("use symlinks in dir-diff mode")),
		OPT_STRING('t', "tool", &difftool_cmd, N_("<tool>"),
			   N_("use the specified diff tool")),
		OPT_BOOL(0, "tool-help", &tool_help,
			 N_("print a list of diff tools that may be used with "
			    "`--tool`")),
		OPT_BOOL(0, "trust-exit-code", &trust_exit_code,
			 N_("make 'git-difftool' exit when an invoked diff "
			    "tool returns a non - zero exit code")),
		OPT_STRING('x', "extcmd", &extcmd, N_("<command>"),
			   N_("specify a custom command for viewing diffs")),
		OPT_END()
	};

	git_config(difftool_config, NULL);
	symlinks = has_symlinks;

	argc = parse_options(argc, argv, prefix, builtin_difftool_options,
			     builtin_difftool_usage, PARSE_OPT_KEEP_UNKNOWN |
			     PARSE_OPT_KEEP_DASHDASH);

	if (tool_help)
		return print_tool_help();

	/* NEEDSWORK: once we no longer spawn anything, remove this */
	setenv(GIT_DIR_ENVIRONMENT, absolute_path(get_git_dir()), 1);
	setenv(GIT_WORK_TREE_ENVIRONMENT, absolute_path(get_git_work_tree()), 1);

	if (use_gui_tool && diff_gui_tool && *diff_gui_tool)
		setenv("GIT_DIFF_TOOL", diff_gui_tool, 1);
	else if (difftool_cmd) {
		if (*difftool_cmd)
			setenv("GIT_DIFF_TOOL", difftool_cmd, 1);
		else
			die(_("no <tool> given for --tool=<tool>"));
	}

	if (extcmd) {
		if (*extcmd)
			setenv("GIT_DIFFTOOL_EXTCMD", extcmd, 1);
		else
			die(_("no <cmd> given for --extcmd=<cmd>"));
	}

	setenv("GIT_DIFFTOOL_TRUST_EXIT_CODE",
	       trust_exit_code ? "true" : "false", 1);

	/*
	 * In directory diff mode, 'git-difftool--helper' is called once
	 * to compare the a / b directories. In file diff mode, 'git diff'
	 * will invoke a separate instance of 'git-difftool--helper' for
	 * each file that changed.
	 */
	if (dir_diff)
		return run_dir_diff(extcmd, symlinks, prefix, argc, argv);
	return run_file_diff(prompt, prefix, argc, argv);
}