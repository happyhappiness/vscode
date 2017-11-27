static void submit_counter (const c_psql_database_t *db,
		const char *type, const char *type_instance,
		const char *value)
{
	value_t values[1];

	if ((NULL == value) || ('\0' == *value))
		return;

	values[0].counter = atoll (value);
	submit (db, type, type_instance, values, 1);
	return;
}