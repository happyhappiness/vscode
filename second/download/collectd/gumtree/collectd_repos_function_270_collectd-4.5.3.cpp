static void submit (const c_psql_database_t *db,
		const char *type, const char *type_instance,
		value_t *values, size_t values_len)
{
	value_list_t vl = VALUE_LIST_INIT;

	vl.values     = values;
	vl.values_len = values_len;
	vl.time       = time (NULL);

	if (C_PSQL_IS_UNIX_DOMAIN_SOCKET (db->host)
			|| (0 == strcmp (db->host, "localhost")))
		sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	else
		sstrncpy (vl.host, db->host, sizeof (vl.host));

	sstrncpy (vl.plugin, "postgresql", sizeof (vl.plugin));
	sstrncpy (vl.plugin_instance, db->database, sizeof (vl.plugin_instance));

	sstrncpy (vl.type, type, sizeof (vl.type));

	if (NULL != type_instance)
		sstrncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));

	plugin_dispatch_values (&vl);
	return;
}