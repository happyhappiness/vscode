static int git_get_colorbool_config(const char *var, const char *value,
		void *cb)
{
	if (!strcmp(var, get_colorbool_slot))
		get_colorbool_found = git_config_colorbool(var, value);
	else if (!strcmp(var, "diff.color"))
		get_diff_color_found = git_config_colorbool(var, value);
	else if (!strcmp(var, "color.ui"))
		get_color_ui_found = git_config_colorbool(var, value);
	return 0;
}