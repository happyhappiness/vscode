void module_register (void)
{
#if IOKIT_HAVE_READ
	plugin_register_init ("apple_sensors", as_init);
	plugin_register_read ("apple_sensors", as_read);
#endif /* IOKIT_HAVE_READ */
}