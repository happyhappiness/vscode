static void set_host (mysql_database_t *db, char *buf, size_t buflen)
{
	if (db->alias)
		sstrncpy (buf, db->alias, buflen);
	else if ((db->host == NULL)
			|| (strcmp ("", db->host) == 0)
			|| (strcmp ("127.0.0.1", db->host) == 0)
			|| (strcmp ("localhost", db->host) == 0))
		sstrncpy (buf, hostname_g, buflen);
	else
		sstrncpy (buf, db->host, buflen);
}