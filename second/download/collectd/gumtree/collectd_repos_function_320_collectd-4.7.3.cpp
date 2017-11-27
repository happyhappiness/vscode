static int c_psql_shutdown (void)
{
	int i;

	if ((NULL == databases) || (0 == databases_num))
		return 0;

	plugin_unregister_read ("postgresql");
	plugin_unregister_shutdown ("postgresql");

	for (i = 0; i < databases_num; ++i)
		c_psql_database_delete (databases + i);

	sfree (databases);
	databases_num = 0;

	udb_query_free (queries, queries_num);
	queries = NULL;
	queries_num = 0;

	return 0;
}