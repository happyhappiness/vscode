char *alias_lookup(const char *alias)
{
	struct config_alias_data data = { alias, NULL };

	read_early_config(config_alias_cb, &data);

	return data.v;
}