void module_register (void)
{
#if DISK_HAVE_READ
	plugin_register_init ("disk", disk_init);
	plugin_register_read ("disk", disk_read);
#endif /* DISK_HAVE_READ */
}