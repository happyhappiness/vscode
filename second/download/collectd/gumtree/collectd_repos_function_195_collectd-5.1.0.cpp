static void submit_derive (const char *type, const char *type_instance,
		derive_t c, apache_t *st)
{
	value_t v;
	v.derive = c;
	submit_value (type, type_instance, v, st);
}