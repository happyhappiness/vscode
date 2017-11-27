void module_register (void)
{
#if BATTERY_HAVE_READ
	plugin_register_init ("battery", battery_init);
	plugin_register_read ("battery", battery_read);
#endif /* BATTERY_HAVE_READ */
}