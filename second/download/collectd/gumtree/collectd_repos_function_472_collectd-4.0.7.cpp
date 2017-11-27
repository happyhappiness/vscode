void module_register (void)
{
#if MEMORY_HAVE_READ
	plugin_register_init ("memory", memory_init);
	plugin_register_read ("memory", memory_read);
#endif /* MEMORY_HAVE_READ */
}