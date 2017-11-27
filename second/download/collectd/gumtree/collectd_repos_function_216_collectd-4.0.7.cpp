void module_register (void)
{
#if LOAD_HAVE_READ
	plugin_register_read ("load", load_read);
#endif
}