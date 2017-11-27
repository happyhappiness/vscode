static int config_set_param (c_psql_query_t *query, const oconfig_item_t *ci)
{
	c_psql_param_t param;
	char          *param_str;

	if ((0 != ci->children_num) || (1 != ci->values_num)
			|| (OCONFIG_TYPE_STRING != ci->values[0].type)) {
		log_err ("Param expects a single string argument.");
		return 1;
	}

	param_str = ci->values[0].value.string;
	if (0 == strcasecmp (param_str, "hostname"))
		param = C_PSQL_PARAM_HOST;
	else if (0 == strcasecmp (param_str, "database"))
		param = C_PSQL_PARAM_DB;
	else if (0 == strcasecmp (param_str, "username"))
		param = C_PSQL_PARAM_USER;
	else {
		log_err ("Invalid parameter \"%s\".", param_str);
		return 1;
	}

	++query->params_num;
	if (NULL == (query->params = (c_psql_param_t *)realloc (query->params,
				query->params_num * sizeof (*query->params)))) {
		log_err ("Out of memory.");
		exit (5);
	}

	query->params[query->params_num - 1] = param;
	return 0;
}