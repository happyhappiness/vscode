static void counter_submit (const char *type, const char *type_instance,
		counter_t value, mysql_database_t *db)
{
	value_t values[1];

	values[0].counter = value;
	submit (type, type_instance, values, STATIC_ARRAY_SIZE (values), db);
}