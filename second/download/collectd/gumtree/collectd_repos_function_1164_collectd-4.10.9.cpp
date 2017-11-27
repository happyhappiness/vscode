void module_register (void)
{
	plugin_register_complex_config ("notify_desktop", c_notify_config);
	plugin_register_init ("notify_desktop", c_notify_init);
	return;
}