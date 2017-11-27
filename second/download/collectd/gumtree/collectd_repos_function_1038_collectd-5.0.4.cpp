static void za_submit_gauge (const char* type, const char* type_instance, gauge_t value)
{
	value_t vv;

	vv.gauge = value;
	za_submit (type, type_instance, &vv, 1);
}