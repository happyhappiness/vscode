static void submit_gauge (const c_psql_database_t *db,
		const char *type, const char *type_instance,
		const char *value)
{
	value_t values[1];

	if ((NULL == value) || ('\0' == *value))
		return;

	values[0].gauge = atof (value);
	submit (db, type, type_instance, values, 1);
	return;
}