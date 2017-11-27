static int c_psql_check_connection (c_psql_database_t *db)
{
	_Bool init = 0;

	if (! db->conn) {
		init = 1;

		/* trigger c_release() */
		if (0 == db->conn_complaint.interval)
			db->conn_complaint.interval = 1;

		c_psql_connect (db);
	}

	if (CONNECTION_OK != PQstatus (db->conn)) {
		PQreset (db->conn);

		/* trigger c_release() */
		if (0 == db->conn_complaint.interval)
			db->conn_complaint.interval = 1;

		if (CONNECTION_OK != PQstatus (db->conn)) {
			c_complain (LOG_ERR, &db->conn_complaint,
					"Failed to connect to database %s (%s): %s",
					db->database, db->instance,
					PQerrorMessage (db->conn));
			return -1;
		}

		db->proto_version = PQprotocolVersion (db->conn);
	}

	db->server_version = PQserverVersion (db->conn);

	if (c_would_release (&db->conn_complaint)) {
		char *server_host;
		int   server_version;

		server_host    = PQhost (db->conn);
		server_version = PQserverVersion (db->conn);

		c_do_release (LOG_INFO, &db->conn_complaint,
				"Successfully %sconnected to database %s (user %s) "
				"at server %s%s%s (server version: %d.%d.%d, "
				"protocol version: %d, pid: %d)", init ? "" : "re",
				PQdb (db->conn), PQuser (db->conn),
				C_PSQL_SOCKET3 (server_host, PQport (db->conn)),
				C_PSQL_SERVER_VERSION3 (server_version),
				db->proto_version, PQbackendPID (db->conn));

		if (3 > db->proto_version)
			log_warn ("Protocol version %d does not support parameters.",
					db->proto_version);
	}
	return 0;
}