static PGresult *c_psql_exec_query_params (c_psql_database_t *db,
		udb_query_t *q, c_psql_user_data_t *data)
{
	char *params[db->max_params_num];
	char  interval[64];
	int   i;

	if ((data == NULL) || (data->params_num == 0))
		return (c_psql_exec_query_noparams (db, q));

	assert (db->max_params_num >= data->params_num);

	for (i = 0; i < data->params_num; ++i) {
		switch (data->params[i]) {
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
			case C_PSQL_PARAM_INTERVAL:
				ssnprintf (interval, sizeof (interval), "%.3f",
						(db->interval > 0)
						? CDTIME_T_TO_DOUBLE (db->interval)
						: plugin_get_interval ());
				params[i] = interval;
				break;
			case C_PSQL_PARAM_INSTANCE:
				params[i] = db->instance;
				break;
			default:
				assert (0);
		}
	}

	return PQexecParams (db->conn, udb_query_get_statement (q),
			data->params_num, NULL,
			(const char *const *) params,
			NULL, NULL, /* return text data */ 0);
}