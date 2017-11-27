static int c_psql_check_connection (c_psql_database_t *db)
{
	/* "ping" */
	PQclear (PQexec (db->conn, "SELECT 42;"));

	if (CONNECTION_OK != PQstatus (db->conn)) {
		PQreset (db->conn);

		/* trigger c_release() */
		if (0 == db->conn_complaint.interval)
			db->conn_complaint.interval = 1;

		if (CONNECTION_OK != PQstatus (db->conn)) {
			c_complain (LOG_ERR, &db->conn_complaint,
					"Failed to connect to database %s: %s",
					db->database, PQerrorMessage (db->conn));
			return -1;
		}

		db->proto_version = PQprotocolVersion (db->conn);
		if (3 > db->proto_version)
			log_warn ("Protocol version %d does not support parameters.",
					db->proto_version);
	}

	c_release (LOG_INFO, &db->conn_complaint,
			"Successfully reconnected to database %s", PQdb (db->conn));
	return 0;
}