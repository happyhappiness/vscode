static c_psql_database_t *c_psql_database_new (const char *name)
{
	c_psql_database_t **tmp;
	c_psql_database_t  *db;

	db = (c_psql_database_t *)malloc (sizeof(*db));
	if (NULL == db) {
		log_err ("Out of memory.");
		return NULL;
	}

	tmp = (c_psql_database_t **)realloc (databases,
			(databases_num + 1) * sizeof (*databases));
	if (NULL == tmp) {
		log_err ("Out of memory.");
		sfree (db);
		return NULL;
	}

	databases = tmp;
	databases[databases_num] = db;
	++databases_num;

	db->conn = NULL;

	C_COMPLAIN_INIT (&db->conn_complaint);

	db->proto_version = 0;
	db->server_version = 0;

	db->max_params_num = 0;

	db->q_prep_areas   = NULL;
	db->queries        = NULL;
	db->queries_num    = 0;

	db->writers        = NULL;
	db->writers_num    = 0;

	pthread_mutex_init (&db->db_lock, /* attrs = */ NULL);

	db->interval   = 0;

	db->commit_interval = 0;
	db->next_commit     = 0;
	db->expire_delay    = 0;

	db->database   = sstrdup (name);
	db->host       = NULL;
	db->port       = NULL;
	db->user       = NULL;
	db->password   = NULL;

	db->instance   = sstrdup (name);

	db->sslmode    = NULL;

	db->krbsrvname = NULL;

	db->service    = NULL;

	db->ref_cnt    = 0;
	return db;
}