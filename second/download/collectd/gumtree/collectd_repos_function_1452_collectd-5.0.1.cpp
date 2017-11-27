static void traffic_submit (derive_t rx, derive_t tx, mysql_database_t *db)
{
	value_t values[2];

	values[0].derive = rx;
	values[1].derive = tx;

	submit ("mysql_octets", NULL, values, STATIC_ARRAY_SIZE (values), db);
}