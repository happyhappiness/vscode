void module_register (void)
{
#if TAPE_HAVE_READ
	plugin_register_init ("tape", tape_init);
	plugin_register_read ("tape", tape_read);
#endif /* TAPE_HAVE_READ */
}