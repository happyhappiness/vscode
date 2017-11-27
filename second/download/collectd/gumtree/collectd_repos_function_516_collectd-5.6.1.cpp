void module_register (void)
{
	plugin_register_init ("nfs", nfs_init);
	plugin_register_read ("nfs", nfs_read);
}