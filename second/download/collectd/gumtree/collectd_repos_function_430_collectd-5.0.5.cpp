static int c_psql_config_database (oconfig_item_t *ci)
{
	c_psql_database_t *db;

	char cb_name[DATA_MAX_NAME_LEN];
	struct timespec cb_interval = { 0, 0 };
	user_data_t ud;

	int i;

	if ((1 != ci->values_num)
			|| (OCONFIG_TYPE_STRING != ci->values[0].type)) {
		log_err ("<Database> expects a single string argument.");
		return 1;
	}

	memset (&ud, 0, sizeof (ud));

	db = c_psql_database_new (ci->values[0].value.string);
	if (db == NULL)
		return -1;

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
		else if (0 == strcasecmp (c->key, "Interval"))
			cf_util_get_cdtime (c, &db->interval);
		else
			log_warn ("Ignoring unknown config key \"%s\".", c->key);
	}

	/* If no `Query' options were given, add the default queries.. */
	if (db->queries_num == 0) {
		for (i = 0; i < def_queries_num; i++)
			udb_query_pick_from_list_by_name (def_queries[i],
					queries, queries_num,
					&db->queries, &db->queries_num);
	}

	if (db->queries_num > 0) {
		db->q_prep_areas = (udb_query_preparation_area_t **) calloc (
				db->queries_num, sizeof (*db->q_prep_areas));

		if (db->q_prep_areas == NULL) {
			log_err ("Out of memory.");
			c_psql_database_delete (db);
			return -1;
		}
	}

	for (i = 0; (size_t)i < db->queries_num; ++i) {
		c_psql_user_data_t *data;
		data = udb_query_get_user_data (db->queries[i]);
		if ((data != NULL) && (data->params_num > db->max_params_num))
			db->max_params_num = data->params_num;

		db->q_prep_areas[i]
			= udb_query_allocate_preparation_area (db->queries[i]);

		if (db->q_prep_areas[i] == NULL) {
			log_err ("Out of memory.");
			c_psql_database_delete (db);
			return -1;
		}
	}

	ud.data = db;
	ud.free_func = c_psql_database_delete;

	ssnprintf (cb_name, sizeof (cb_name), "postgresql-%s", db->database);

	CDTIME_T_TO_TIMESPEC (db->interval, &cb_interval);

	plugin_register_complex_read ("postgresql", cb_name, c_psql_read,
			/* interval = */ (db->interval > 0) ? &cb_interval : NULL,
			&ud);
	return 0;
}