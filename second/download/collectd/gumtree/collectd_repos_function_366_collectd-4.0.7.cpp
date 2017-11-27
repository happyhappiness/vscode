void module_register (void)
{
#if ENTROPY_HAVE_READ
	plugin_register_read ("entropy", entropy_read);
#endif
}