static void c_psql_database_delete (void *data)
{
	size_t i;

	c_psql_database_t *db = data;

	PQfinish (db->conn);
	db->conn = NULL;

	if (db->q_prep_areas)
		for (i = 0; i < db->queries_num; ++i)
			udb_query_delete_preparation_area (db->q_prep_areas[i]);
	free (db->q_prep_areas);

	sfree (db->queries);
	db->queries_num = 0;

	sfree (db->database);
	sfree (db->host);
	sfree (db->port);
	sfree (db->user);
	sfree (db->password);

	sfree (db->sslmode);

	sfree (db->krbsrvname);

	sfree (db->service);
	return;
}