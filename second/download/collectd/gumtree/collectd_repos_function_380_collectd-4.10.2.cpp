static int c_psql_read (user_data_t *ud)
{
	c_psql_database_t *db;

	int success = 0;
	int i;

	if ((ud == NULL) || (ud->data == NULL)) {
		log_err ("c_psql_read: Invalid user data.");
		return -1;
	}

	db = ud->data;

	assert (NULL != db->database);

	if (0 != c_psql_check_connection (db))
		return -1;

	for (i = 0; i < db->queries_num; ++i)
	{
		udb_query_preparation_area_t *prep_area;
		udb_query_t *q;

		prep_area = db->q_prep_areas[i];
		q = db->queries[i];

		if ((0 != db->server_version)
				&& (udb_query_check_version (q, db->server_version) <= 0))
			continue;

		if (0 == c_psql_exec_query (db, q, prep_area))
			success = 1;
	}

	if (! success)
		return -1;
	return 0;
}