void module_register (void)
{
#if USERS_HAVE_READ
	plugin_register_read ("users", users_read);
#endif
}