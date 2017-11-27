static int openvpn_config (const char *key, const char *value)
{
	if (strcasecmp ("StatusFile", key) == 0)
	{
		char    *status_file, *status_name, *filename;
		int     status_version, i;
		vpn_status_t *temp;

		/* try to detect the status file format */
		status_version = version_detect (value);

		if (status_version == 0)
		{
			WARNING ("openvpn plugin: unable to detect status version, \
					discarding status file \"%s\".", value);
			return (1);
		}

		status_file = sstrdup (value);
		if (status_file == NULL)
		{
			char errbuf[1024];
			WARNING ("openvpn plugin: sstrdup failed: %s",
					sstrerror (errno, errbuf, sizeof (errbuf)));
			return (1);
		}

		/* it determines the file name as string starting at location filename + 1 */
		filename = strrchr (status_file, (int) '/');
		if (filename == NULL)
		{
			/* status_file is already the file name only */
			status_name = status_file;
		}
		else
		{
			/* doesn't waste memory, uses status_file starting at filename + 1 */
			status_name = filename + 1;
		}

		/* scan the list looking for a clone */
		for (i = 0; i < vpn_num; i++)
		{
			if (strcasecmp (vpn_list[i]->name, status_name) == 0)
			{
				WARNING ("openvpn plugin: status filename \"%s\" "
						"already used, please choose a "
						"different one.", status_name);
				sfree (status_file);
				return (1);
			}
		}

		/* create a new vpn element since file, version and name are ok */
		temp = (vpn_status_t *) malloc (sizeof (vpn_status_t));
		if (temp == NULL)
		{
			char errbuf[1024];
			ERROR ("openvpn plugin: malloc failed: %s",
					sstrerror (errno, errbuf, sizeof (errbuf)));
			sfree (status_file);
			return (1);
		}
		temp->file = status_file;
		temp->version = status_version;
		temp->name = status_name;

		vpn_list = (vpn_status_t **) realloc (vpn_list, (vpn_num + 1) * sizeof (vpn_status_t *));
		if (vpn_list == NULL)
		{
			char errbuf[1024];
			ERROR ("openvpn plugin: realloc failed: %s",
					sstrerror (errno, errbuf, sizeof (errbuf)));

			sfree (temp->file);
			sfree (temp);
			return (1);
		}

		vpn_list[vpn_num] = temp;
		vpn_num++;

		DEBUG ("openvpn plugin: status file \"%s\" added", temp->file);

	} /* if (strcasecmp ("StatusFile", key) == 0) */
	else if ((strcasecmp ("CollectCompression", key) == 0)
		|| (strcasecmp ("Compression", key) == 0)) /* old, deprecated name */
	{
		if (IS_FALSE (value))
			collect_compression = 0;
		else
			collect_compression = 1;
	} /* if (strcasecmp ("CollectCompression", key) == 0) */
	else if (strcasecmp ("ImprovedNamingSchema", key) == 0)
	{
		if (IS_TRUE (value))
		{
			DEBUG ("openvpn plugin: using the new naming schema");
			new_naming_schema = 1;
		}
		else
		{
			new_naming_schema = 0;
		}
	} /* if (strcasecmp ("ImprovedNamingSchema", key) == 0) */
	else if (strcasecmp("CollectUserCount", key) == 0)
	{
		if (IS_TRUE(value))
			collect_user_count = 1;
		else
			collect_user_count = 0;
	} /* if (strcasecmp("CollectUserCount", key) == 0) */
	else if (strcasecmp("CollectIndividualUsers", key) == 0)
	{
		if (IS_FALSE (value))
			collect_individual_users = 0;
		else
			collect_individual_users = 1;
	} /* if (strcasecmp("CollectIndividualUsers", key) == 0) */
	else
	{
		return (-1);
	}

	return (0);
}