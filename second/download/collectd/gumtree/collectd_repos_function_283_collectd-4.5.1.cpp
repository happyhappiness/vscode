static int config_set_column (c_psql_query_t *query, const oconfig_item_t *ci)
{
	c_psql_col_t *col;

	int i;

	if ((0 != ci->children_num)
			|| (1 > ci->values_num) || (2 < ci->values_num)) {
		log_err ("Column expects either one or two arguments.");
		return 1;
	}

	for (i = 0; i < ci->values_num; ++i) {
		if (OCONFIG_TYPE_STRING != ci->values[i].type) {
			log_err ("Column expects either one or two string arguments.");
			return 1;
		}
	}

	++query->cols_num;
	if (NULL == (query->cols = (c_psql_col_t *)realloc (query->cols,
				query->cols_num * sizeof (*query->cols)))) {
		log_err ("Out of memory.");
		exit (5);
	}

	col = query->cols + query->cols_num - 1;

	col->ds_type = -1;

	col->type = sstrdup (ci->values[0].value.string);
	col->type_instance = (2 == ci->values_num)
		? sstrdup (ci->values[1].value.string) : NULL;
	return 0;
}