void module_register (void)
{
	plugin_register_read ("nfs", nfs_read);
}