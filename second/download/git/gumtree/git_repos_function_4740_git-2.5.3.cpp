static int git_show_branch_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "showbranch.default")) {
		if (!value)
			return config_error_nonbool(var);
		/*
		 * default_arg is now passed to parse_options(), so we need to
		 * mimic the real argv a bit better.
		 */
		if (!default_num) {
			default_alloc = 20;
			default_arg = xcalloc(default_alloc, sizeof(*default_arg));
			default_arg[default_num++] = "show-branch";
		} else if (default_alloc <= default_num + 1) {
			default_alloc = default_alloc * 3 / 2 + 20;
			REALLOC_ARRAY(default_arg, default_alloc);
		}
		default_arg[default_num++] = xstrdup(value);
		default_arg[default_num] = NULL;
		return 0;
	}

	if (!strcmp(var, "color.showbranch")) {
		showbranch_use_color = git_config_colorbool(var, value);
		return 0;
	}

	return git_color_default_config(var, value, cb);
}