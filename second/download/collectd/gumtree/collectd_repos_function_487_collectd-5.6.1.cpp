static int c_psql_connect (c_psql_database_t *db)
{
	char  conninfo[4096];
	char *buf     = conninfo;
	int   buf_len = sizeof (conninfo);
	int   status;

	if ((! db) || (! db->database))
		return -1;

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
	db->proto_version = PQprotocolVersion (db->conn);
	return 0;
}