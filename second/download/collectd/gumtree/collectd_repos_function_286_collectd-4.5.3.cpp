static int c_psql_config_query (oconfig_item_t *ci)
{
	c_psql_query_t *query;

	int i;

	if ((1 != ci->values_num)
			|| (OCONFIG_TYPE_STRING != ci->values[0].type)) {
		log_err ("<Query> expects a single string argument.");
		return 1;
	}

	query = c_psql_query_new (ci->values[0].value.string);

	for (i = 0; i < ci->children_num; ++i) {
		oconfig_item_t *c = ci->children + i;

		if (0 == strcasecmp (c->key, "Query"))
			config_set_s ("Query", &query->query, c);
		else if (0 == strcasecmp (c->key, "Param"))
			config_set_param (query, c);
		else if (0 == strcasecmp (c->key, "Column"))
			config_set_column (query, c);
		else if (0 == strcasecmp (c->key, "MinPGVersion"))
			config_set_i ("MinPGVersion", &query->min_pg_version, c);
		else if (0 == strcasecmp (c->key, "MaxPGVersion"))
			config_set_i ("MaxPGVersion", &query->max_pg_version, c);
		else
			log_warn ("Ignoring unknown config key \"%s\".", c->key);
	}

	for (i = 0; i < queries_num - 1; ++i) {
		c_psql_query_t *q = queries + i;

		if ((0 == strcasecmp (q->name, query->name))
				&& (q->min_pg_version <= query->max_pg_version)
				&& (query->min_pg_version <= q->max_pg_version)) {
			log_err ("Ignoring redefinition (with overlapping version ranges) "
					"of query \"%s\".", query->name);
			c_psql_query_delete (query);
			--queries_num;
			return 1;
		}
	}

	if (query->min_pg_version > query->max_pg_version) {
		log_err ("Query \"%s\": MinPGVersion > MaxPGVersion.",
				query->name);
		c_psql_query_delete (query);
		--queries_num;
		return 1;
	}

	if (NULL == query->query) {
		log_err ("Query \"%s\" does not include an SQL query string - "
				"please check your configuration.", query->name);
		c_psql_query_delete (query);
		--queries_num;
		return 1;
	}
	return 0;
}