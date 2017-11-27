void plugin_set_dir (const char *dir)
{
	if (plugindir != NULL)
		free (plugindir);

	if (dir == NULL)
		plugindir = NULL;
	else if ((plugindir = strdup (dir)) == NULL)
	{
		char errbuf[1024];
		ERROR ("strdup failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
	}
}