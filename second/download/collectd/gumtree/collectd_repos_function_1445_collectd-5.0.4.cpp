static int mysql_config_database (oconfig_item_t *ci) /* {{{ */
{
	mysql_database_t *db;
	int status = 0;
	int i;

	if ((ci->values_num != 1)
	    || (ci->values[0].type != OCONFIG_TYPE_STRING))
	{
		WARNING ("mysql plugin: The `Database' block "
			 "needs exactly one string argument.");
		return (-1);
	}

	db = (mysql_database_t *) malloc (sizeof (*db));
	if (db == NULL)
	{
		ERROR ("mysql plugin: malloc failed.");
		return (-1);
	}
	memset (db, 0, sizeof (*db));

	/* initialize all the pointers */
	db->host     = NULL;
	db->user     = NULL;
	db->pass     = NULL;
	db->database = NULL;
	db->socket   = NULL;
	db->con      = NULL;

	/* trigger a notification, if it's not running */
	db->slave_io_running  = 1;
	db->slave_sql_running = 1;

	status = cf_util_get_string (ci, &db->instance);
	if (status != 0)
	{
		sfree (db);
		return (status);
	}
	assert (db->instance != NULL);

	/* Fill the `mysql_database_t' structure.. */
	for (i = 0; i < ci->children_num; i++)
	{
		oconfig_item_t *child = ci->children + i;

		if (strcasecmp ("Host", child->key) == 0)
			status = cf_util_get_string (child, &db->host);
		else if (strcasecmp ("User", child->key) == 0)
			status = cf_util_get_string (child, &db->user);
		else if (strcasecmp ("Password", child->key) == 0)
			status = cf_util_get_string (child, &db->pass);
		else if (strcasecmp ("Port", child->key) == 0)
		{
			status = cf_util_get_port_number (child);
			if (status > 0)
			{
				db->port = status;
				status = 0;
			}
		}
		else if (strcasecmp ("Socket", child->key) == 0)
			status = cf_util_get_string (child, &db->socket);
		else if (strcasecmp ("Database", child->key) == 0)
			status = cf_util_get_string (child, &db->database);
		else if (strcasecmp ("MasterStats", child->key) == 0)
			status = cf_util_get_boolean (child, &db->master_stats);
		else if (strcasecmp ("SlaveStats", child->key) == 0)
			status = cf_util_get_boolean (child, &db->slave_stats);
		else if (strcasecmp ("SlaveNotifications", child->key) == 0)
			status = cf_util_get_boolean (child, &db->slave_notif);
		else
		{
			WARNING ("mysql plugin: Option `%s' not allowed here.", child->key);
			status = -1;
		}

		if (status != 0)
			break;
	}

	/* If all went well, register this database for reading */
	if (status == 0)
	{
		user_data_t ud;
		char cb_name[DATA_MAX_NAME_LEN];

		DEBUG ("mysql plugin: Registering new read callback: %s",
				(db->database != NULL) ? db->database : "<default>");

		memset (&ud, 0, sizeof (ud));
		ud.data = (void *) db;
		ud.free_func = mysql_database_free;

		if (db->database != NULL)
			ssnprintf (cb_name, sizeof (cb_name), "mysql-%s",
					db->database);
		else
			sstrncpy (cb_name, "mysql", sizeof (cb_name));

		plugin_register_complex_read (/* group = */ NULL, cb_name,
					      mysql_read,
					      /* interval = */ NULL, &ud);
	}
	else
	{
		mysql_database_free (db);
		return (-1);
	}

	return (0);
}