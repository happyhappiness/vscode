void module_register (void)
{
#if CPU_HAVE_READ
	plugin_register_init ("cpu", init);
	plugin_register_read ("cpu", cpu_read);
#endif /* CPU_HAVE_READ */
}