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
			c_psql_exec_query (db, j);

		++success;
	}

	if (! success)
		return -1;
	return 0;
}