static void za_submit_gauge (const char* type, const char* type_instance, gauge_t value)
{
	value_t values[1];

	values[0].gauge = value;

	za_submit (type, type_instance, values, STATIC_ARRAY_SIZE(values));
}