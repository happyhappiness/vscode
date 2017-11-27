void module_register (void)
{
	plugin_register_init ("swap", swap_init);
	plugin_register_read ("swap", swap_read);
}