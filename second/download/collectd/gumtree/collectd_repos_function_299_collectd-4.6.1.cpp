static int c_psql_exec_query (c_psql_database_t *db, udb_query_t *q)
{
	PGresult *res;

	c_psql_user_data_t *data;

	const char *host;

	char **column_names;
	char **column_values;
	int    column_num;

	int rows_num;
	int status;
	int i;

	/* The user data may hold parameter information, but may be NULL. */
	data = udb_query_get_user_data (q);

	/* Versions up to `3' don't know how to handle parameters. */
	if (3 <= db->proto_version)
		res = c_psql_exec_query_params (db, q, data);
	else if ((NULL == data) || (0 == data->params_num))
		res = c_psql_exec_query_noparams (db, q);
	else {
		log_err ("Connection to database \"%s\" does not support parameters "
				"(protocol version %d) - cannot execute query \"%s\".",
				db->database, db->proto_version,
				udb_query_get_name (q));
		return -1;
	}

	column_names = NULL;
	column_values = NULL;

#define BAIL_OUT(status) \
	sfree (column_names); \
	sfree (column_values); \
	PQclear (res); \
	return status

	if (PGRES_TUPLES_OK != PQresultStatus (res)) {
		log_err ("Failed to execute SQL query: %s",
				PQerrorMessage (db->conn));
		log_info ("SQL query was: %s",
				udb_query_get_statement (q));
		BAIL_OUT (-1);
	}

	rows_num = PQntuples (res);
	if (1 > rows_num) {
		BAIL_OUT (0);
	}

	column_num = PQnfields (res);
	column_names = (char **) calloc (column_num, sizeof (char *));
	if (NULL == column_names) {
		log_err ("calloc failed.");
		BAIL_OUT (-1);
	}

	column_values = (char **) calloc (column_num, sizeof (char *));
	if (NULL == column_values) {
		log_err ("calloc failed.");
		BAIL_OUT (-1);
	}
	
	for (i = 0; i < column_num; i++) {
		/* Pointers returned by `PQfname' are freed by `PQclear' via
		 * `BAIL_OUT'. */
		column_names[i] = PQfname (res, i);
		if (NULL == column_names[i]) {
			log_err ("PQfname (%i) failed.", i);
			BAIL_OUT (-1);
		}
	}

	if (C_PSQL_IS_UNIX_DOMAIN_SOCKET (db->host)
			|| (0 == strcmp (db->host, "localhost")))
		host = hostname_g;
	else
		host = db->host;

	status = udb_query_prepare_result (q, host, "postgresql",
			db->database, column_names, (size_t) column_num);
	if (0 != status) {
		log_err ("udb_query_prepare_result failed with status %i.",
				status);
		BAIL_OUT (-1);
	}

	for (i = 0; i < rows_num; ++i) {
		int j;

		for (j = 0; j < column_num; j++) {
			/* Pointers returned by `PQgetvalue' are freed by `PQclear' via
			 * `BAIL_OUT'. */
			column_values[j] = PQgetvalue (res, /* row = */ i, /* col = */ j);
			if (NULL == column_values[j]) {
				log_err ("PQgetvalue (%i, %i) failed.", i, j);
				break;
			}
		}

		/* check for an error */
		if (j < column_num)
			continue;

		status = udb_query_handle_result (q, column_values);
		if (status != 0) {
			log_err ("udb_query_handle_result failed with status %i.",
					status);
		}
	} /* for (i = 0; i < rows_num; ++i) */

	BAIL_OUT (0);
#undef BAIL_OUT
}