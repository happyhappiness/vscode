static int c_psql_init (void)
{
	int i;

	if ((NULL == databases) || (0 == databases_num))
		return 0;

	for (i = 0; i < databases_num; ++i) {
		c_psql_database_t *db = databases + i;

		char  conninfo[4096];
		char *buf     = conninfo;
		int   buf_len = sizeof (conninfo);
		int   status;

		char *server_host;
		int   server_version;

		/* this will happen during reinitialization */
		if (NULL != db->conn) {
			c_psql_check_connection (db);
			continue;
		}

		status = ssnprintf (buf, buf_len, "dbname = '%s'", db->database);
		if (0 < status) {
			buf     += status;
			buf_len -= status;
		}

		C_PSQL_PAR_APPEND (buf, buf_len, "host",       db->host);
		C_PSQL_PAR_APPEND (buf, buf_len, "port",       db->port);
		C_PSQL_PAR_APPEND (buf, buf_len, "user",       db->user);
		C_PSQL_PAR_APPEND (buf, buf_len, "password",   db->password);
		C_PSQL_PAR_APPEND (buf, buf_len, "sslmode",    db->sslmode);
		C_PSQL_PAR_APPEND (buf, buf_len, "krbsrvname", db->krbsrvname);
		C_PSQL_PAR_APPEND (buf, buf_len, "service",    db->service);

		db->conn = PQconnectdb (conninfo);
		if (0 != c_psql_check_connection (db))
			continue;

		db->proto_version = PQprotocolVersion (db->conn);

		server_host    = PQhost (db->conn);
		server_version = PQserverVersion (db->conn);
		log_info ("Successfully connected to database %s (user %s) "
				"at server %s%s%s (server version: %d.%d.%d, "
				"protocol version: %d, pid: %d)",
				PQdb (db->conn), PQuser (db->conn),
				C_PSQL_SOCKET3 (server_host, PQport (db->conn)),
				C_PSQL_SERVER_VERSION3 (server_version),
				db->proto_version, PQbackendPID (db->conn));

		if (3 > db->proto_version)
			log_warn ("Protocol version %d does not support parameters.",
					db->proto_version);
	}

	plugin_register_read ("postgresql", c_psql_read);
	plugin_register_shutdown ("postgresql", c_psql_shutdown);
	return 0;
}