static int mysql_config (oconfig_item_t *ci) /* {{{ */
{
	mysql_database_t *db;
	int plugin_block;
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

	plugin_block = 1;
	if (strcasecmp ("Plugin", ci->key) == 0)
	{
		db->instance = NULL;
	}
	else if (strcasecmp ("Database", ci->key) == 0)
	{
		plugin_block = 0;
		status = mysql_config_set_string (&db->instance, ci);
		if (status != 0)
		{
			sfree (db);
			return (status);
		}
		assert (db->instance != NULL);
	}
	else
	{
		ERROR ("mysql plugin: mysql_config: "
				"Invalid key: %s", ci->key);
		return (-1);
	}

	/* Fill the `mysql_database_t' structure.. */
	for (i = 0; i < ci->children_num; i++)
	{
		oconfig_item_t *child = ci->children + i;

		if (strcasecmp ("Host", child->key) == 0)
			status = mysql_config_set_string (&db->host, child);
		else if (strcasecmp ("User", child->key) == 0)
			status = mysql_config_set_string (&db->user, child);
		else if (strcasecmp ("Password", child->key) == 0)
			status = mysql_config_set_string (&db->pass, child);
		else if (strcasecmp ("Port", child->key) == 0)
			status = mysql_config_set_int (&db->port, child);
		else if (strcasecmp ("Socket", child->key) == 0)
			status = mysql_config_set_string (&db->socket, child);
		/* Check if we're currently handling the `Plugin' block. If so,
		 * handle `Database' _blocks_, too. */
		else if ((plugin_block != 0)
				&& (strcasecmp ("Database", child->key) == 0)
				&& (child->children != NULL))
		{
			/* If `plugin_block > 1', there has been at least one
			 * `Database' block */
			plugin_block++;
			status = mysql_config (child);
		}
		/* Now handle ordinary `Database' options (without children) */
		else if ((strcasecmp ("Database", child->key) == 0)
				&& (child->children == NULL))
			status = mysql_config_set_string (&db->database, child);
		else if (strcasecmp ("MasterStats", child->key) == 0)
			status = mysql_config_set_boolean (&db->master_stats, child);
		else if (strcasecmp ("SlaveStats", child->key) == 0)
			status = mysql_config_set_boolean (&db->slave_stats, child);
		else if (strcasecmp ("SlaveNotifications", child->key) == 0)
			status = mysql_config_set_boolean (&db->slave_notif, child);
		else
		{
			WARNING ("mysql plugin: Option `%s' not allowed here.", child->key);
			status = -1;
		}

		if (status != 0)
			break;
	}

	/* Check if there were any `Database' blocks. */
	if (plugin_block > 1)
	{
		/* There were connection blocks. Don't use any legacy stuff. */
		if ((db->host != NULL)
			|| (db->user != NULL)
			|| (db->pass != NULL)
			|| (db->database != NULL)
			|| (db->socket != NULL)
			|| (db->port != 0))
		{
			WARNING ("mysql plugin: At least one <Database> "
					"block has been found. The legacy "
					"configuration will be ignored.");
		}
		mysql_database_free (db);
		return (0);
	}
	else if (plugin_block != 0)
	{
		WARNING ("mysql plugin: You're using the legacy "
				"configuration options. Please consider "
				"updating your configuration!");
	}

	/* Check that all necessary options have been given. */
	while (status == 0)
	{
		/* Zero is allowed and automatically handled by
		 * `mysql_real_connect'. */
		if ((db->port < 0) || (db->port > 65535))
		{
			ERROR ("mysql plugin: Database %s: Port number out "
					"of range: %i",
					(db->instance != NULL)
					? db->instance
					: "<legacy>",
					db->port);
			status = -1;
		}
		break;
	} /* while (status == 0) */

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

		plugin_register_complex_read (cb_name, mysql_read,
					      /* interval = */ NULL, &ud);
	}
	else
	{
		mysql_database_free (db);
		return (-1);
	}

	return (0);
}