static void load_submit (gauge_t snum, gauge_t mnum, gauge_t lnum)
{
	value_t values[3];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].gauge = snum;
	values[1].gauge = mnum;
	values[2].gauge = lnum;

	vl.values = values;
	vl.values_len = STATIC_ARRAY_SIZE (values);
	vl.time = time (NULL);
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "load", sizeof (vl.plugin));
	sstrncpy (vl.type, "load", sizeof (vl.type));

	plugin_dispatch_values (&vl);
}