static int git_get_color_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, get_color_slot)) {
		if (!value)
			config_error_nonbool(var);
		color_parse(value, var, parsed_color);
		get_color_found = 1;
	}
	return 0;
}