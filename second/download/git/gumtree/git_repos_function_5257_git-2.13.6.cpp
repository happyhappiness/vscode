static int git_branch_config(const char *var, const char *value, void *cb)
{
	const char *slot_name;

	if (starts_with(var, "column."))
		return git_column_config(var, value, "branch", &colopts);
	if (!strcmp(var, "color.branch")) {
		branch_use_color = git_config_colorbool(var, value);
		return 0;
	}
	if (skip_prefix(var, "color.branch.", &slot_name)) {
		int slot = parse_branch_color_slot(slot_name);
		if (slot < 0)
			return 0;
		if (!value)
			return config_error_nonbool(var);
		return color_parse(value, branch_colors[slot]);
	}
	return git_color_default_config(var, value, cb);
}