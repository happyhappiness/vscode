void module_register (void)
{
#if CPUFREQ_HAVE_READ
	plugin_register_init ("cpufreq", cpufreq_init);
	plugin_register_read ("cpufreq", cpufreq_read);
#endif /* CPUFREQ_HAVE_READ */
}