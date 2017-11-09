static void write_config(struct string_list *config)
{
	int i;

	for (i = 0; i < config->nr; i++) {
		if (git_config_parse_parameter(config->items[i].string,
					       write_one_config, NULL) < 0)
			die(_("unable to write parameters to config file"));
	}
}