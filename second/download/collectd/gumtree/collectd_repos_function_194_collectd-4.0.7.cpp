void module_register (void)
{
#if WIRELESS_HAVE_READ
	plugin_register_read ("wireless", wireless_read);
#endif /* WIRELESS_HAVE_READ */
}