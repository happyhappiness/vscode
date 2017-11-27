void module_register (void)
{
#if VSERVER_HAVE_READ
	plugin_register_init ("vserver", vserver_init);
	plugin_register_read ("vserver", vserver_read);
#endif /* VSERVER_HAVE_READ */
}