static c_psql_query_t *c_psql_query_get (const char *name, int server_version)
{
	int i;

	for (i = 0; i < queries_num; ++i)
		if (0 == strcasecmp (name, queries[i].name)
				&& ((-1 == server_version)
					|| ((queries[i].min_pg_version <= server_version)
						&& (server_version <= queries[i].max_pg_version))))
			return queries + i;
	return NULL;
}