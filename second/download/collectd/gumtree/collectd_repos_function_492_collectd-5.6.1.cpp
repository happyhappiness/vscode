static int c_psql_read (user_data_t *ud)
{
	c_psql_database_t *db;

	int success = 0;

	if ((ud == NULL) || (ud->data == NULL)) {
		log_err ("c_psql_read: Invalid user data.");
		return -1;
	}

	db = ud->data;

	assert (NULL != db->database);
	assert (NULL != db->instance);
	assert (NULL != db->queries);

	pthread_mutex_lock (&db->db_lock);

	if (0 != c_psql_check_connection (db)) {
		pthread_mutex_unlock (&db->db_lock);
		return -1;
	}

	for (size_t i = 0; i < db->queries_num; ++i)
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

	pthread_mutex_unlock (&db->db_lock);

	if (! success)
		return -1;
	return 0;
}