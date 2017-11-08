static int git_show_branch_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "showbranch.default")) {
		if (!value)
			return config_error_nonbool(var);
		/*
		 * default_arg is now passed to parse_options(), so we need to
		 * mimic the real argv a bit better.
		 */
		if (!default_args.argc)
			argv_array_push(&default_args, "show-branch");
		argv_array_push(&default_args, value);
		return 0;
	}

	if (!strcmp(var, "color.showbranch")) {
		showbranch_use_color = git_config_colorbool(var, value);
		return 0;
	}

	return git_color_default_config(var, value, cb);
}