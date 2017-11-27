void module_register (void)
{
	plugin_register_init ("zfs_arc", za_init);
	plugin_register_read ("zfs_arc", za_read);
}