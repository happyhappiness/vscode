static void za_submit_counts (char *type_instance, counter_t demand_data, counter_t demand_metadata,
	counter_t prefetch_data, counter_t prefetch_metadata)
{
	value_t values[4];

	values[0].counter = demand_data;
	values[1].counter = demand_metadata;
	values[2].counter = prefetch_data;
	values[3].counter = prefetch_metadata;

	za_submit ("arc_counts", type_instance, values, STATIC_ARRAY_SIZE(values));
}