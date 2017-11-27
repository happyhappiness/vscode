static void submit_gauge (const char *type, const char *type_instance,
		gauge_t g, apache_t *st)
{
	value_t v;
	v.gauge = g;
	submit_value (type, type_instance, v, st);
}