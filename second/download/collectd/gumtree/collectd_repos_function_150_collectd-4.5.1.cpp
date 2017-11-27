void module_register (void)
{
	plugin_register_init ("cpu", init);
	plugin_register_read ("cpu", cpu_read);
}