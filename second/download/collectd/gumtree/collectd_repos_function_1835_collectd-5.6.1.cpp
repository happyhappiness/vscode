static void mysql_database_free (void *arg) /* {{{ */
{
	mysql_database_t *db;

	DEBUG ("mysql plugin: mysql_database_free (arg = %p);", arg);

	db = arg;

	if (db == NULL)
		return;

	if (db->con != NULL)
		mysql_close (db->con);

	sfree (db->alias);
	sfree (db->host);
	sfree (db->user);
	sfree (db->pass);
	sfree (db->socket);
	sfree (db->instance);
	sfree (db->database);
	sfree (db->key);
	sfree (db->cert);
	sfree (db->ca);
	sfree (db->capath);
	sfree (db->cipher);
	sfree (db);
}