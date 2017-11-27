static int c_psql_shutdown (void)
{
	int i;

	if ((NULL == databases) || (0 == databases_num))
		return 0;

	plugin_unregister_read ("postgresql");
	plugin_unregister_shutdown ("postgresql");

	for (i = 0; i < databases_num; ++i) {
		c_psql_database_t *db = databases + i;
		c_psql_database_delete (db);
	}

	sfree (databases);
	databases_num = 0;

	for (i = 0; i < queries_num; ++i) {
		c_psql_query_t *query = queries + i;
		c_psql_query_delete (query);
	}

	sfree (queries);
	queries_num = 0;
	return 0;
}