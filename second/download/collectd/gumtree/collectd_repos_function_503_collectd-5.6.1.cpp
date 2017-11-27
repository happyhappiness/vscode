static int c_psql_config (oconfig_item_t *ci)
{
	static int have_def_config = 0;

	if (0 == have_def_config) {
		oconfig_item_t *c;

		have_def_config = 1;

		c = oconfig_parse_file (C_PSQL_DEFAULT_CONF);
		if (NULL == c)
			log_err ("Failed to read default config ("C_PSQL_DEFAULT_CONF").");
		else
			c_psql_config (c);

		if (NULL == queries)
			log_err ("Default config ("C_PSQL_DEFAULT_CONF") did not define "
					"any queries - please check your installation.");
	}

	for (int i = 0; i < ci->children_num; ++i) {
		oconfig_item_t *c = ci->children + i;

		if (0 == strcasecmp (c->key, "Query"))
			udb_query_create (&queries, &queries_num, c,
					/* callback = */ config_query_callback);
		else if (0 == strcasecmp (c->key, "Writer"))
			c_psql_config_writer (c);
		else if (0 == strcasecmp (c->key, "Database"))
			c_psql_config_database (c);
		else
			log_warn ("Ignoring unknown config key \"%s\".", c->key);
	}
	return 0;
}