int plugin_unregister_config (const char *name)
{
	cf_unregister (name);
	return (0);
}