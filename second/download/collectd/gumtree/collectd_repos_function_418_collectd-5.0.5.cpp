static c_psql_database_t *c_psql_database_new (const char *name)
{
	c_psql_database_t *db;

	db = (c_psql_database_t *)malloc (sizeof (*db));
	if (NULL == db) {
		log_err ("Out of memory.");
		return NULL;
	}

	db->conn = NULL;

	C_COMPLAIN_INIT (&db->conn_complaint);

	db->proto_version = 0;
	db->server_version = 0;

	db->max_params_num = 0;

	db->q_prep_areas   = NULL;
	db->queries        = NULL;
	db->queries_num    = 0;

	db->interval   = 0;

	db->database   = sstrdup (name);
	db->host       = NULL;
	db->port       = NULL;
	db->user       = NULL;
	db->password   = NULL;

	db->sslmode    = NULL;

	db->krbsrvname = NULL;

	db->service    = NULL;
	return db;
}