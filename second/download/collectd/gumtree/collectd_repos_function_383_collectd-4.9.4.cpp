static int c_psql_config_database (oconfig_item_t *ci)
{
	c_psql_database_t *db;

	int i;

	if ((1 != ci->values_num)
			|| (OCONFIG_TYPE_STRING != ci->values[0].type)) {
		log_err ("<Database> expects a single string argument.");
		return 1;
	}

	db = c_psql_database_new (ci->values[0].value.string);

	for (i = 0; i < ci->children_num; ++i) {
		oconfig_item_t *c = ci->children + i;

		if (0 == strcasecmp (c->key, "Host"))
			config_set_s ("Host", &db->host, c);
		else if (0 == strcasecmp (c->key, "Port"))
			config_set_s ("Port", &db->port, c);
		else if (0 == strcasecmp (c->key, "User"))
			config_set_s ("User", &db->user, c);
		else if (0 == strcasecmp (c->key, "Password"))
			config_set_s ("Password", &db->password, c);
		else if (0 == strcasecmp (c->key, "SSLMode"))
			config_set_s ("SSLMode", &db->sslmode, c);
		else if (0 == strcasecmp (c->key, "KRBSrvName"))
			config_set_s ("KRBSrvName", &db->krbsrvname, c);
		else if (0 == strcasecmp (c->key, "Service"))
			config_set_s ("Service", &db->service, c);
		else if (0 == strcasecmp (c->key, "Query"))
			udb_query_pick_from_list (c, queries, queries_num,
					&db->queries, &db->queries_num);
		else
			log_warn ("Ignoring unknown config key \"%s\".", c->key);
	}

	/* If no `Query' options were given, add the default queries.. */
	if (db->queries_num == 0)
	{
		for (i = 0; i < def_queries_num; i++)
			udb_query_pick_from_list_by_name (def_queries[i],
					queries, queries_num,
					&db->queries, &db->queries_num);
	}

	for (i = 0; (size_t)i < db->queries_num; ++i) {
		c_psql_user_data_t *data;
		data = udb_query_get_user_data (db->queries[i]);
		if ((data != NULL) && (data->params_num > db->max_params_num))
			db->max_params_num = data->params_num;
	}
	return 0;
}