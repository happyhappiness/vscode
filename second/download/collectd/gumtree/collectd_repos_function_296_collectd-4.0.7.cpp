void module_register (void)
{
#if SERIAL_HAVE_READ
	plugin_register_read ("serial", serial_read);
#endif /* SERIAL_HAVE_READ */
}