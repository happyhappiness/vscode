static void c_psql_database_delete (c_psql_database_t *db)
{
	PQfinish (db->conn);

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