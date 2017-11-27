void module_register(void)
{
	plugin_register_complex_config("sigrok", sigrok_config);
	plugin_register_init("sigrok", sigrok_init);
	plugin_register_shutdown("sigrok", sigrok_shutdown);
}