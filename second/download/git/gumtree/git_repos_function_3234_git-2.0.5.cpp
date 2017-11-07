int remote_is_configured(const char *name)
{
	int i;
	read_config();

	for (i = 0; i < remotes_nr; i++)
		if (!strcmp(name, remotes[i]->name))
			return 1;
	return 0;
}