
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

static void get_color(const char *def_color)
{
	get_color_found = 0;
	parsed_color[0] = '\0';
	git_config_with_options(git_get_color_config, NULL,
				&given_config_source, respect_includes);

	if (!get_color_found && def_color)
		color_parse(def_color, "command line", parsed_color);

	fputs(parsed_color, stdout);
}

static int get_colorbool_found;
static int get_diff_color_found;
