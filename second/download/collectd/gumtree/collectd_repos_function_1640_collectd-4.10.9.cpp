int plugin_unregister_init (const char *name)
{
	return (plugin_unregister (list_init, name));
}