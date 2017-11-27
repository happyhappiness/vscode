static PGresult *c_psql_exec_query_params (c_psql_database_t *db,
		c_psql_query_t *query)
{
	char *params[db->max_params_num];
	int   i;

	assert (db->max_params_num >= query->params_num);

	for (i = 0; i < query->params_num; ++i) {
		switch (query->params[i]) {
			case C_PSQL_PARAM_HOST:
				params[i] = C_PSQL_IS_UNIX_DOMAIN_SOCKET (db->host)
					? "localhost" : db->host;
				break;
			case C_PSQL_PARAM_DB:
				params[i] = db->database;
				break;
			case C_PSQL_PARAM_USER:
				params[i] = db->user;
				break;
			default:
				assert (0);
		}
	}

	return PQexecParams (db->conn, query->query, query->params_num, NULL,
			(const char *const *)((0 == query->params_num) ? NULL : params),
			NULL, NULL, /* return text data */ 0);
}