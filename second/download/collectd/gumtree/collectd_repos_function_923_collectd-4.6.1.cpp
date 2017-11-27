static void qcache_submit (counter_t hits, counter_t inserts,
		counter_t not_cached, counter_t lowmem_prunes,
		gauge_t queries_in_cache)
{
	value_t values[5];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].counter = hits;
	values[1].counter = inserts;
	values[2].counter = not_cached;
	values[3].counter = lowmem_prunes;
	values[4].gauge   = queries_in_cache;

	vl.values = values;
	vl.values_len = 5;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "mysql", sizeof (vl.plugin));
	sstrncpy (vl.type, "mysql_qcache", sizeof (vl.type));

	plugin_dispatch_values (&vl);
}