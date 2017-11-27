static MYSQL *getconnection (mysql_database_t *db)
{
	if (db->is_connected)
	{
		int status;

		status = mysql_ping (db->con);
		if (status == 0)
			return (db->con);

		WARNING ("mysql plugin: Lost connection to instance \"%s\": %s",
				db->instance, mysql_error (db->con));
	}
	db->is_connected = 0;

	if (db->con == NULL)
	{
		db->con = mysql_init (NULL);
		if (db->con == NULL)
		{
			ERROR ("mysql plugin: mysql_init failed: %s",
					mysql_error (db->con));
			return (NULL);
		}
	}

	/* Configure TCP connect timeout (default: 0) */
	db->con->options.connect_timeout = db->timeout;

	if (mysql_real_connect (db->con, db->host, db->user, db->pass,
				db->database, db->port, db->socket, 0) == NULL)
	{
		ERROR ("mysql plugin: Failed to connect to database %s "
				"at server %s: %s",
				(db->database != NULL) ? db->database : "<none>",
				(db->host != NULL) ? db->host : "localhost",
				mysql_error (db->con));
		return (NULL);
	}

	INFO ("mysql plugin: Successfully connected to database %s "
			"at server %s (server version: %s, protocol version: %d)",
			(db->database != NULL) ? db->database : "<none>",
			mysql_get_host_info (db->con),
			mysql_get_server_info (db->con),
			mysql_get_proto_info (db->con));

	db->is_connected = 1;
	return (db->con);
}