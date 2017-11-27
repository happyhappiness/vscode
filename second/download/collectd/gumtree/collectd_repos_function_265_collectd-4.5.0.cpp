static c_psql_query_t *c_psql_query_new (const char *name)
{
	c_psql_query_t *query;

	++queries_num;
	if (NULL == (queries = (c_psql_query_t *)realloc (queries,
				queries_num * sizeof (*queries)))) {
		log_err ("Out of memory.");
		exit (5);
	}
	query = queries + queries_num - 1;

	query->name  = sstrdup (name);
	query->query = NULL;

	query->params     = NULL;
	query->params_num = 0;

	query->cols     = NULL;
	query->cols_num = 0;

	query->min_pg_version = 0;
	query->max_pg_version = INT_MAX;
	return query;
}