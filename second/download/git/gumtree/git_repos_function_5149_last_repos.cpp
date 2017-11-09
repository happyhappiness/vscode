static int get_colorbool(const char *var, int print)
{
	get_colorbool_slot = var;
	get_colorbool_found = -1;
	get_diff_color_found = -1;
	get_color_ui_found = -1;
	config_with_options(git_get_colorbool_config, NULL,
			    &given_config_source, &config_options);

	if (get_colorbool_found < 0) {
		if (!strcmp(get_colorbool_slot, "color.diff"))
			get_colorbool_found = get_diff_color_found;
		if (get_colorbool_found < 0)
			get_colorbool_found = get_color_ui_found;
	}

	if (get_colorbool_found < 0)
		/* default value if none found in config */
		get_colorbool_found = GIT_COLOR_AUTO;

	get_colorbool_found = want_color(get_colorbool_found);

	if (print) {
		printf("%s\n", get_colorbool_found ? "true" : "false");
		return 0;
	} else
		return get_colorbool_found ? 0 : 1;
}