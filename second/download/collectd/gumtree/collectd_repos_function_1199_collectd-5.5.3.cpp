static int cldap_config_add (oconfig_item_t *ci) /* {{{ */
{
	cldap_t *st;
	int i;
	int status;

	st = malloc (sizeof (*st));
	if (st == NULL)
	{
		ERROR ("openldap plugin: malloc failed.");
		return (-1);
	}
	memset (st, 0, sizeof (*st));

	status = cf_util_get_string (ci, &st->name);
	if (status != 0)
	{
		sfree (st);
		return (status);
	}

	st->starttls = 0;
	st->timeout = -1;
	st->verifyhost = 1;
	st->version = LDAP_VERSION3;

	for (i = 0; i < ci->children_num; i++)
	{
		oconfig_item_t *child = ci->children + i;

		if (strcasecmp ("CACert", child->key) == 0)
			status = cf_util_get_string (child, &st->cacert);
		else if (strcasecmp ("StartTLS", child->key) == 0)
			status = cf_util_get_boolean (child, &st->starttls);
		else if (strcasecmp ("Timeout", child->key) == 0)
			status = cf_util_get_int (child, &st->timeout);
		else if (strcasecmp ("URL", child->key) == 0)
			status = cf_util_get_string (child, &st->url);
		else if (strcasecmp ("VerifyHost", child->key) == 0)
			status = cf_util_get_boolean (child, &st->verifyhost);
		else if (strcasecmp ("Version", child->key) == 0)
			status = cf_util_get_int (child, &st->version);
		else
		{
			WARNING ("openldap plugin: Option `%s' not allowed here.",
					child->key);
			status = -1;
		}

		if (status != 0)
			break;
	}

	/* Check if struct is complete.. */
	if ((status == 0) && (st->url == NULL))
	{
		ERROR ("openldap plugin: Instance `%s': "
				"No URL has been configured.",
				st->name);
		status = -1;
	}

	/* Check if URL is valid */
	if ((status == 0) && (st->url != NULL))
	{
		LDAPURLDesc *ludpp;
		int rc;

		if ((rc = ldap_url_parse (st->url, &ludpp)) != 0)
		{
			ERROR ("openldap plugin: Instance `%s': "
				"Invalid URL: `%s'",
				st->name, st->url);
			status = -1;
		}

		if ((status == 0) && (ludpp->lud_host != NULL))
		{
			st->host = strdup (ludpp->lud_host);
		}

		ldap_free_urldesc (ludpp);
	}

	if (status == 0)
	{
		user_data_t ud;
		char callback_name[3*DATA_MAX_NAME_LEN];

		memset (&ud, 0, sizeof (ud));
		ud.data = st;

		memset (callback_name, 0, sizeof (callback_name));
		ssnprintf (callback_name, sizeof (callback_name),
				"openldap/%s/%s",
				(st->host != NULL) ? st->host : hostname_g,
				(st->name != NULL) ? st->name : "default"),

		status = plugin_register_complex_read (/* group = */ NULL,
				/* name      = */ callback_name,
				/* callback  = */ cldap_read_host,
				/* interval  = */ NULL,
				/* user_data = */ &ud);
	}

	if (status != 0)
	{
		cldap_free (st);
		return (-1);
	}

	return (0);
}