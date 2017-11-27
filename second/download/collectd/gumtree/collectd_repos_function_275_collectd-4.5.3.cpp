static PGresult *c_psql_exec_query_noparams (c_psql_database_t *db,
		c_psql_query_t *query)
{
	return PQexec (db->conn, query->query);
}