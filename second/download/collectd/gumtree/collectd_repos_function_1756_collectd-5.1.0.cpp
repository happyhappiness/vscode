int plugin_unregister_flush (const char *name)
{
	return (plugin_unregister (list_flush, name));
}