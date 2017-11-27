static void qcache_submit (counter_t hits, counter_t inserts,
		counter_t not_cached, counter_t lowmem_prunes,
		gauge_t queries_in_cache, mysql_database_t *db)
{
	value_t values[5];

	values[0].counter = hits;
	values[1].counter = inserts;
	values[2].counter = not_cached;
	values[3].counter = lowmem_prunes;
	values[4].gauge   = queries_in_cache;

	submit ("mysql_qcache", NULL, values, STATIC_ARRAY_SIZE (values), db);
}