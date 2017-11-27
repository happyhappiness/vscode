static void set_plugin_instance (mysql_database_t *db,
		char *buf, size_t buflen)
{
	/* XXX legacy mode - no plugin_instance */
	if (db->instance == NULL)
		sstrncpy (buf, "", buflen);
	else
		sstrncpy (buf, db->instance, buflen);
}