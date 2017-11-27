int plugin_register_log (const char *name,
		plugin_log_cb callback, user_data_t const *ud)
{
	return (create_register_callback (&list_log, name,
				(void *) callback, ud));
}