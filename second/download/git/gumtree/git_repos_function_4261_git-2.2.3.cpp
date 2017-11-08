static const char *implicit_ident_advice(void)
{
	char *user_config = NULL;
	char *xdg_config = NULL;
	int config_exists;

	home_config_paths(&user_config, &xdg_config, "config");
	config_exists = file_exists(user_config) || file_exists(xdg_config);
	free(user_config);
	free(xdg_config);

	if (config_exists)
		return _(implicit_ident_advice_config);
	else
		return _(implicit_ident_advice_noconfig);

}