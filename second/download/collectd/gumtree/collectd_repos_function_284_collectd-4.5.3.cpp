static int set_query (c_psql_database_t *db, const char *name)
{
	c_psql_query_t *query;

	query = c_psql_query_get (name, -1);
	if (NULL == query) {
		log_err ("Query \"%s\" not found - please check your configuration.",
				name);
		return 1;
	}

	++db->queries_num;
	if (NULL == (db->queries = (c_psql_query_t **)realloc (db->queries,
				db->queries_num * sizeof (*db->queries)))) {
		log_err ("Out of memory.");
		exit (5);
	}

	if (query->params_num > db->max_params_num)
		db->max_params_num = query->params_num;

	db->queries[db->queries_num - 1] = query;
	return 0;
}