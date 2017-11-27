static void za_submit_bytes (counter_t read, counter_t write)
{
	value_t values[2];

	values[0].counter = read;
	values[1].counter = write;

	za_submit ("arc_l2_bytes", "", values, STATIC_ARRAY_SIZE(values));
}