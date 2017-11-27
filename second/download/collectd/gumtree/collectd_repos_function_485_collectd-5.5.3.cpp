static int c_psql_write (const data_set_t *ds, const value_list_t *vl,
		user_data_t *ud)
{
	c_psql_database_t *db;

	char time_str[32];
	char values_name_str[1024];
	char values_type_str[1024];
	char values_str[1024];

	const char *params[9];

	int success = 0;
	int i;

	if ((ud == NULL) || (ud->data == NULL)) {
		log_err ("c_psql_write: Invalid user data.");
		return -1;
	}

	db = ud->data;
	assert (db->database != NULL);
	assert (db->writers != NULL);

	if (cdtime_to_iso8601 (time_str, sizeof (time_str), vl->time) == 0) {
		log_err ("c_psql_write: Failed to convert time to ISO 8601 format");
		return -1;
	}

	if (values_name_to_sqlarray (ds,
				values_name_str, sizeof (values_name_str)) == NULL)
		return -1;

#define VALUE_OR_NULL(v) ((((v) == NULL) || (*(v) == '\0')) ? NULL : (v))

	params[0] = time_str;
	params[1] = vl->host;
	params[2] = vl->plugin;
	params[3] = VALUE_OR_NULL(vl->plugin_instance);
	params[4] = vl->type;
	params[5] = VALUE_OR_NULL(vl->type_instance);
	params[6] = values_name_str;

#undef VALUE_OR_NULL

	if( db->expire_delay > 0 && vl->time < (cdtime() - vl->interval - db->expire_delay) ) {
		log_info ("c_psql_write: Skipped expired value @ %s - %s/%s-%s/%s-%s/%s", 
			params[0], params[1], params[2], params[3], params[4], params[5], params[6] );
		return 0;
        }

	pthread_mutex_lock (&db->db_lock);

	if (0 != c_psql_check_connection (db)) {
		pthread_mutex_unlock (&db->db_lock);
		return -1;
	}

	if ((db->commit_interval > 0)
			&& (db->next_commit == 0))
		c_psql_begin (db);

	for (i = 0; i < db->writers_num; ++i) {
		c_psql_writer_t *writer;
		PGresult *res;

		writer = db->writers[i];

		if (values_type_to_sqlarray (ds,
					values_type_str, sizeof (values_type_str),
					writer->store_rates) == NULL) {
			pthread_mutex_unlock (&db->db_lock);
			return -1;
		}

		if (values_to_sqlarray (ds, vl,
					values_str, sizeof (values_str),
					writer->store_rates) == NULL) {
			pthread_mutex_unlock (&db->db_lock);
			return -1;
		}

		params[7] = values_type_str;
		params[8] = values_str;

		res = PQexecParams (db->conn, writer->statement,
				STATIC_ARRAY_SIZE (params), NULL,
				(const char *const *)params,
				NULL, NULL, /* return text data */ 0);

		if ((PGRES_COMMAND_OK != PQresultStatus (res))
				&& (PGRES_TUPLES_OK != PQresultStatus (res))) {
			PQclear (res);

			if ((CONNECTION_OK != PQstatus (db->conn))
					&& (0 == c_psql_check_connection (db))) {
				/* try again */
				res = PQexecParams (db->conn, writer->statement,
						STATIC_ARRAY_SIZE (params), NULL,
						(const char *const *)params,
						NULL, NULL, /* return text data */ 0);

				if ((PGRES_COMMAND_OK == PQresultStatus (res))
						|| (PGRES_TUPLES_OK == PQresultStatus (res))) {
					PQclear (res);
					success = 1;
					continue;
				}
			}

			log_err ("Failed to execute SQL query: %s",
					PQerrorMessage (db->conn));
			log_info ("SQL query was: '%s', "
					"params: %s, %s, %s, %s, %s, %s, %s, %s",
					writer->statement,
					params[0], params[1], params[2], params[3],
					params[4], params[5], params[6], params[7]);

			/* this will abort any current transaction -> restart */
			if (db->next_commit > 0)
				c_psql_commit (db);

			pthread_mutex_unlock (&db->db_lock);
			return -1;
		}

		PQclear (res);
		success = 1;
	}

	if ((db->next_commit > 0)
			&& (cdtime () > db->next_commit))
		c_psql_commit (db);

	pthread_mutex_unlock (&db->db_lock);

	if (! success)
		return -1;
	return 0;
}