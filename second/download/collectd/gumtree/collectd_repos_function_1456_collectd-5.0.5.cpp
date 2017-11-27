static void set_host (mysql_database_t *db, char *buf, size_t buflen)
{
	if ((db->host == NULL)
			|| (strcmp ("", db->host) == 0)
			|| (strcmp ("localhost", db->host) == 0))
		sstrncpy (buf, hostname_g, buflen);
	else
		sstrncpy (buf, db->host, buflen);
}