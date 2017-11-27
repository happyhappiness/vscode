void module_register (void)
{
	plugin_register_init ("tape", tape_init);
	plugin_register_read ("tape", tape_read);
}