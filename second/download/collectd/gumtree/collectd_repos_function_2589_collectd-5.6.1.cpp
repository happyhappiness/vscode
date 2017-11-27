void plugin_set_dir (const char *dir)
{
	sfree (plugindir);

	if (dir == NULL)
	{
		plugindir = NULL;
		return;
	}

	plugindir = strdup (dir);
	if (plugindir == NULL)
		ERROR ("plugin_set_dir: strdup(\"%s\") failed", dir);
}