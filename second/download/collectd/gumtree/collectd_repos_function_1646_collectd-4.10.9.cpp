int plugin_unregister_shutdown (const char *name)
{
	return (plugin_unregister (list_shutdown, name));
}