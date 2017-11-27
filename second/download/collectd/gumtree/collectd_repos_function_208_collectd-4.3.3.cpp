void module_register (void)
{
	plugin_register_init ("disk", disk_init);
	plugin_register_read ("disk", disk_read);
}