void module_register (void)
{
	plugin_register_config("tokyotyrant", tt_config,
			config_keys, config_keys_num);
	plugin_register_read("tokyotyrant", tt_read);
	plugin_register_shutdown("tokyotyrant", tt_shutdown);
}