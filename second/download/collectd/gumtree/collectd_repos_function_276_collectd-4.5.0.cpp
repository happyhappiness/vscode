static int c_psql_exec_query (c_psql_database_t *db, int idx)
{
	c_psql_query_t *query;
	PGresult       *res;

	int rows, cols;
	int i;

	if (idx >= db->queries_num)
		return -1;

	query = db->queries[idx];

	if (3 <= db->proto_version)
		res = c_psql_exec_query_params (db, query);
	else if (0 == query->params_num)
		res = c_psql_exec_query_noparams (db, query);
	else {
		log_err ("Connection to database \"%s\" does not support parameters "
				"(protocol version %d) - cannot execute query \"%s\".",
				db->database, db->proto_version, query->name);
		return -1;
	}

	if (PGRES_TUPLES_OK != PQresultStatus (res)) {
		log_err ("Failed to execute SQL query: %s",
				PQerrorMessage (db->conn));
		log_info ("SQL query was: %s", query->query);
		PQclear (res);
		return -1;
	}

	rows = PQntuples (res);
	if (1 > rows)
		return 0;

	cols = PQnfields (res);
	if (query->cols_num != cols) {
		log_err ("SQL query returned wrong number of fields "
				"(expected: %i, got: %i)", query->cols_num, cols);
		log_info ("SQL query was: %s", query->query);
		return -1;
	}

	for (i = 0; i < rows; ++i) {
		int j;

		for (j = 0; j < cols; ++j) {
			c_psql_col_t col = query->cols[j];

			char *value = PQgetvalue (res, i, j);

			if (col.ds_type == DS_TYPE_COUNTER)
				submit_counter (db, col.type, col.type_instance, value);
			else if (col.ds_type == DS_TYPE_GAUGE)
				submit_gauge (db, col.type, col.type_instance, value);
		}
	}
	return 0;
}