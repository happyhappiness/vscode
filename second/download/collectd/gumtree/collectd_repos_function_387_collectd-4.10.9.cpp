static int c_psql_shutdown (void)
{
	plugin_unregister_read_group ("postgresql");

	udb_query_free (queries, queries_num);
	queries = NULL;
	queries_num = 0;

	return 0;
}