int plugin_register_flush (const char *name,
		plugin_flush_cb callback, user_data_t *ud)
{
	return (create_register_callback (&list_flush, name,
				(void *) callback, ud));
}