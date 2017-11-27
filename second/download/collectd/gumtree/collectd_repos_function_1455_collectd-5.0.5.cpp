static MYSQL *getconnection (mysql_database_t *db)
{
	if (db->state != 0)
	{
		int err;
		if ((err = mysql_ping (db->con)) != 0)
		{
			/* Assured by "mysql_config_database" */
			assert (db->instance != NULL);
			WARNING ("mysql_ping failed for instance \"%s\": %s",
					db->instance,
					mysql_error (db->con));
			db->state = 0;
		}
		else
		{
			db->state = 1;
			return (db->con);
		}
	}

	if ((db->con = mysql_init (db->con)) == NULL)
	{
		ERROR ("mysql_init failed: %s", mysql_error (db->con));
		db->state = 0;
		return (NULL);
	}

	if (mysql_real_connect (db->con, db->host, db->user, db->pass,
				db->database, db->port, db->socket, 0) == NULL)
	{
		ERROR ("mysql plugin: Failed to connect to database %s "
				"at server %s: %s",
				(db->database != NULL) ? db->database : "<none>",
				(db->host != NULL) ? db->host : "localhost",
				mysql_error (db->con));
		db->state = 0;
		return (NULL);
	}
	else
	{
		INFO ("mysql plugin: Successfully connected to database %s "
				"at server %s (server version: %s, protocol version: %d)",
				(db->database != NULL) ? db->database : "<none>",
				mysql_get_host_info (db->con),
				mysql_get_server_info (db->con),
				mysql_get_proto_info (db->con));
		db->state = 1;
		return (db->con);
	}
}