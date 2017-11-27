static c_psql_database_t *c_psql_database_new (const char *name)
{
	c_psql_database_t *db;

	++databases_num;
	if (NULL == (databases = (c_psql_database_t *)realloc (databases,
				databases_num * sizeof (*databases)))) {
		log_err ("Out of memory.");
		exit (5);
	}

	db = databases + (databases_num - 1);

	db->conn = NULL;

	C_COMPLAIN_INIT (&db->conn_complaint);

	db->proto_version = 0;
	db->server_version = 0;

	db->max_params_num = 0;

	db->queries        = NULL;
	db->queries_num    = 0;

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