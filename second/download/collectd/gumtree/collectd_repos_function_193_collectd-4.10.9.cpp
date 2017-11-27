static void submit_counter (const char *type, const char *type_instance,
		counter_t c, apache_t *st)
{
	value_t v;
	v.counter = c;
	submit_value (type, type_instance, v, st);
}