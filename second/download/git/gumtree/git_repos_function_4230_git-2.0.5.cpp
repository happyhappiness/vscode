static int git_branch_config(const char *var, const char *value, void *cb)
{
	if (starts_with(var, "column."))
		return git_column_config(var, value, "branch", &colopts);
	if (!strcmp(var, "color.branch")) {
		branch_use_color = git_config_colorbool(var, value);
		return 0;
	}
	if (starts_with(var, "color.branch.")) {
		int slot = parse_branch_color_slot(var, 13);
		if (slot < 0)
			return 0;
		if (!value)
			return config_error_nonbool(var);
		color_parse(value, var, branch_colors[slot]);
		return 0;
	}
	return git_color_default_config(var, value, cb);
}