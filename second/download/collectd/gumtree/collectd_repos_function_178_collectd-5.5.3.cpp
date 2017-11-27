static int config_add (oconfig_item_t *ci)
{
	apache_t *st;
	int i;
	int status;

	st = malloc (sizeof (*st));
	if (st == NULL)
	{
		ERROR ("apache plugin: malloc failed.");
		return (-1);
	}
	memset (st, 0, sizeof (*st));

	st->timeout = -1;

	status = cf_util_get_string (ci, &st->name);
	if (status != 0)
	{
		sfree (st);
		return (status);
	}
	assert (st->name != NULL);

	for (i = 0; i < ci->children_num; i++)
	{
		oconfig_item_t *child = ci->children + i;

		if (strcasecmp ("URL", child->key) == 0)
			status = cf_util_get_string (child, &st->url);
		else if (strcasecmp ("Host", child->key) == 0)
			status = cf_util_get_string (child, &st->host);
		else if (strcasecmp ("User", child->key) == 0)
			status = cf_util_get_string (child, &st->user);
		else if (strcasecmp ("Password", child->key) == 0)
			status = cf_util_get_string (child, &st->pass);
		else if (strcasecmp ("VerifyPeer", child->key) == 0)
			status = cf_util_get_boolean (child, &st->verify_peer);
		else if (strcasecmp ("VerifyHost", child->key) == 0)
			status = cf_util_get_boolean (child, &st->verify_host);
		else if (strcasecmp ("CACert", child->key) == 0)
			status = cf_util_get_string (child, &st->cacert);
		else if (strcasecmp ("SSLCiphers", child->key) == 0)
			status = cf_util_get_string (child, &st->ssl_ciphers);
		else if (strcasecmp ("Server", child->key) == 0)
			status = cf_util_get_string (child, &st->server);
		else if (strcasecmp ("Timeout", child->key) == 0)
			status = cf_util_get_int (child, &st->timeout);
		else
		{
			WARNING ("apache plugin: Option `%s' not allowed here.",
					child->key);
			status = -1;
		}

		if (status != 0)
			break;
	}

	/* Check if struct is complete.. */
	if ((status == 0) && (st->url == NULL))
	{
		ERROR ("apache plugin: Instance `%s': "
				"No URL has been configured.",
				st->name);
		status = -1;
	}

	if (status == 0)
	{
		user_data_t ud;
		char callback_name[3*DATA_MAX_NAME_LEN];

		memset (&ud, 0, sizeof (ud));
		ud.data = st;
		ud.free_func = (void *) apache_free;

		memset (callback_name, 0, sizeof (callback_name));
		ssnprintf (callback_name, sizeof (callback_name),
				"apache/%s/%s",
				(st->host != NULL) ? st->host : hostname_g,
				(st->name != NULL) ? st->name : "default");

		status = plugin_register_complex_read (/* group = */ NULL,
				/* name      = */ callback_name,
				/* callback  = */ apache_read_host,
				/* interval  = */ NULL,
				/* user_data = */ &ud);
	}

	if (status != 0)
	{
		apache_free (st);
		return (-1);
	}

	return (0);
}