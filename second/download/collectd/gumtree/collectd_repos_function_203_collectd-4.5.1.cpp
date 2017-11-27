void module_register (void)
{
	plugin_register_init ("battery", battery_init);
	plugin_register_read ("battery", battery_read);
}