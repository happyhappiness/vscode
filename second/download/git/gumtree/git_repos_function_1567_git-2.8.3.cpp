int git_color_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "color.ui")) {
		git_use_color_default = git_config_colorbool(var, value);
		return 0;
	}

	return 0;
}