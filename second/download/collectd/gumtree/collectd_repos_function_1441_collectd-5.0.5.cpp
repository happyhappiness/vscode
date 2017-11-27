static void
process_stat_struct (int which, const void *ptr, const char *dev, const char *mac,
			 const char *type_name, const char *misc_name)
{
	uint32_t misc = 0;
	int i;

	assert (which >= 1);
	assert (which < STATIC_ARRAY_SIZE (bounds));

	for (i = bounds[which - 1]; i < bounds[which]; i++)
	{
		uint32_t val = *(uint32_t *)(((char *) ptr) + specs[i].offset) ;

		if (item_watched (i) && (val != 0))
			submit_derive (dev, type_name, specs[i].name, mac, val);

		if (item_summed (i))
			misc += val;
	}
	
	if (misc != 0)
		submit_derive (dev, type_name, misc_name, mac, misc);

}