static void c_psql_query_delete (c_psql_query_t *query)
{
	int i;

	sfree (query->name);
	sfree (query->query);

	sfree (query->params);
	query->params_num = 0;

	for (i = 0; i < query->cols_num; ++i) {
		sfree (query->cols[i].type);
		sfree (query->cols[i].type_instance);
	}
	sfree (query->cols);
	query->cols_num = 0;
	return;
}