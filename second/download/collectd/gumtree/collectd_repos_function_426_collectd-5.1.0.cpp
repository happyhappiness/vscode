static int config_query_param_add (udb_query_t *q, oconfig_item_t *ci)
{
	c_psql_user_data_t *data;
	const char *param_str;

	c_psql_param_t *tmp;

	data = udb_query_get_user_data (q);
	if (NULL == data) {
		data = (c_psql_user_data_t *) smalloc (sizeof (*data));
		if (NULL == data) {
			log_err ("Out of memory.");
			return -1;
		}
		memset (data, 0, sizeof (*data));
		data->params = NULL;
	}

	tmp = (c_psql_param_t *) realloc (data->params,
			(data->params_num + 1) * sizeof (c_psql_param_t));
	if (NULL == tmp) {
		log_err ("Out of memory.");
		return -1;
	}
	data->params = tmp;

	param_str = ci->values[0].value.string;
	if (0 == strcasecmp (param_str, "hostname"))
		data->params[data->params_num] = C_PSQL_PARAM_HOST;
	else if (0 == strcasecmp (param_str, "database"))
		data->params[data->params_num] = C_PSQL_PARAM_DB;
	else if (0 == strcasecmp (param_str, "username"))
		data->params[data->params_num] = C_PSQL_PARAM_USER;
	else if (0 == strcasecmp (param_str, "interval"))
		data->params[data->params_num] = C_PSQL_PARAM_INTERVAL;
	else {
		log_err ("Invalid parameter \"%s\".", param_str);
		return 1;
	}

	data->params_num++;
	udb_query_set_user_data (q, data);

	return (0);
}