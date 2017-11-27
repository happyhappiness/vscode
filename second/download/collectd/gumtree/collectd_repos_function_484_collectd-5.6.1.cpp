static int c_psql_commit (c_psql_database_t *db)
{
	PGresult *r = PQexec (db->conn, "COMMIT");

	int status = 1;

	if (r != NULL) {
		if (PGRES_COMMAND_OK == PQresultStatus (r)) {
			db->next_commit = 0;
			log_debug ("Successfully committed transaction.");
			status = 0;
		}
		else
			log_warn ("Failed to commit transaction: %s",
					PQerrorMessage (db->conn));
		PQclear (r);
	}
	return status;
}