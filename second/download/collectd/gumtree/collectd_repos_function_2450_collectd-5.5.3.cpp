void plugin_log_available_writers (void)
{
	log_list_callbacks (&list_write, "Available write targets:");
}