static void threads_submit (gauge_t running, gauge_t connected, gauge_t cached,
		counter_t created, mysql_database_t *db)
{
	value_t values[4];

	values[0].gauge   = running;
	values[1].gauge   = connected;
	values[2].gauge   = cached;
	values[3].counter = created;

	submit ("mysql_threads", NULL, values, STATIC_ARRAY_SIZE (values), db);
}