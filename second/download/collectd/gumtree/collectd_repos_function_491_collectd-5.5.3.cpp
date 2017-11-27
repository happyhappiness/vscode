static int c_psql_config_database (oconfig_item_t *ci)
{
	c_psql_database_t *db;

	char cb_name[DATA_MAX_NAME_LEN];
	struct timespec cb_interval = { 0, 0 };
	user_data_t ud;

	static _Bool have_flush = 0;

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
			cf_util_get_string (c, &db->host);
		else if (0 == strcasecmp (c->key, "Port"))
			cf_util_get_service (c, &db->port);
		else if (0 == strcasecmp (c->key, "User"))
			cf_util_get_string (c, &db->user);
		else if (0 == strcasecmp (c->key, "Password"))
			cf_util_get_string (c, &db->password);
		else if (0 == strcasecmp (c->key, "Instance"))
			cf_util_get_string (c, &db->instance);
		else if (0 == strcasecmp (c->key, "SSLMode"))
			cf_util_get_string (c, &db->sslmode);
		else if (0 == strcasecmp (c->key, "KRBSrvName"))
			cf_util_get_string (c, &db->krbsrvname);
		else if (0 == strcasecmp (c->key, "Service"))
			cf_util_get_string (c, &db->service);
		else if (0 == strcasecmp (c->key, "Query"))
			udb_query_pick_from_list (c, queries, queries_num,
					&db->queries, &db->queries_num);
		else if (0 == strcasecmp (c->key, "Writer"))
			config_add_writer (c, writers, writers_num,
					&db->writers, &db->writers_num);
		else if (0 == strcasecmp (c->key, "Interval"))
			cf_util_get_cdtime (c, &db->interval);
		else if (strcasecmp ("CommitInterval", c->key) == 0)
			cf_util_get_cdtime (c, &db->commit_interval);
		else if (strcasecmp ("ExpireDelay", c->key) == 0)
			cf_util_get_cdtime (c, &db->expire_delay);
		else
			log_warn ("Ignoring unknown config key \"%s\".", c->key);
	}

	/* If no `Query' options were given, add the default queries.. */
	if ((db->queries_num == 0) && (db->writers_num == 0)){
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

	ssnprintf (cb_name, sizeof (cb_name), "postgresql-%s", db->instance);

	if (db->queries_num > 0) {
		CDTIME_T_TO_TIMESPEC (db->interval, &cb_interval);

		++db->ref_cnt;
		plugin_register_complex_read ("postgresql", cb_name, c_psql_read,
				/* interval = */ (db->interval > 0) ? &cb_interval : NULL,
				&ud);
	}
	if (db->writers_num > 0) {
		++db->ref_cnt;
		plugin_register_write (cb_name, c_psql_write, &ud);

		if (! have_flush) {
			/* flush all */
			plugin_register_flush ("postgresql",
					c_psql_flush, /* user data = */ NULL);
			have_flush = 1;
		}

		/* flush this connection only */
		++db->ref_cnt;
		plugin_register_flush (cb_name, c_psql_flush, &ud);
	}
	else if (db->commit_interval > 0) {
		log_warn ("Database '%s': You do not have any writers assigned to "
				"this database connection. Setting 'CommitInterval' does "
				"not have any effect.", db->database);
	}
	return 0;
}