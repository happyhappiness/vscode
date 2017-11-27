void module_register (void)
{
	plugin_register_read ("users", users_read);
}