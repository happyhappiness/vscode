void module_register (void)
{
#if NFS_HAVE_READ
	plugin_register_read ("nfs", nfs_read);
#endif
}