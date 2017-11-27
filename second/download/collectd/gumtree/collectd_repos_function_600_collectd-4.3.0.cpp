static oconfig_item_t *cf_read_dir (const char *dir, int depth)
{
	oconfig_item_t *root = NULL;
	DIR *dh;
	struct dirent *de;
	char name[1024];
	int status;

	assert (depth < CF_MAX_DEPTH);

	dh = opendir (dir);
	if (dh == NULL)
	{
		char errbuf[1024];
		ERROR ("configfile: opendir failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (NULL);
	}

	root = (oconfig_item_t *) malloc (sizeof (oconfig_item_t));
	if (root == NULL)
	{
		ERROR ("configfile: malloc failed.");
		return (NULL);
	}
	memset (root, '\0', sizeof (oconfig_item_t));

	while ((de = readdir (dh)) != NULL)
	{
		oconfig_item_t *temp;

		if ((de->d_name[0] == '.') || (de->d_name[0] == '\0'))
			continue;

		status = snprintf (name, sizeof (name), "%s/%s",
				dir, de->d_name);
		if (status >= sizeof (name))
		{
			ERROR ("configfile: Not including `%s/%s' because its"
					" name is too long.",
					dir, de->d_name);
			continue;
		}

		temp = cf_read_generic (name, depth);
		if (temp == NULL)
			continue;

		cf_ci_append_children (root, temp);
		sfree (temp->children);
		sfree (temp);
	}

	return (root);
}