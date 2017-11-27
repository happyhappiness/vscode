static void traffic_submit (counter_t rx, counter_t tx, mysql_database_t *db)
{
	value_t values[2];

	values[0].counter = rx;
	values[1].counter = tx;

	submit ("mysql_octets", NULL, values, STATIC_ARRAY_SIZE (values), db);
}