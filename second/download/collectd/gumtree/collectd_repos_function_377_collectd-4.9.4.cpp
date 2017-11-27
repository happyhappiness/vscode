static int c_psql_read (void)
{
	int success = 0;
	int i;

	for (i = 0; i < databases_num; ++i) {
		c_psql_database_t *db = databases + i;

		int j;

		assert (NULL != db->database);

		if (0 != c_psql_check_connection (db))
			continue;

		for (j = 0; j < db->queries_num; ++j)
		{
			udb_query_t *q;

			q = db->queries[j];

			if ((0 != db->server_version)
				&& (udb_query_check_version (q, db->server_version) <= 0))
				continue;

			c_psql_exec_query (db, q);
		}

		++success;
	}

	if (! success)
		return -1;
	return 0;
}