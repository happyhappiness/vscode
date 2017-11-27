static void za_submit_size (gauge_t size, gauge_t size_target, gauge_t limit_min, gauge_t limit_max)
{
	value_t values[4];

	values[0].gauge = size;
	values[1].gauge = size_target;
	values[2].gauge = limit_min;
	values[3].gauge = limit_max;

	za_submit ("arc_size", "", values, STATIC_ARRAY_SIZE(values));
}