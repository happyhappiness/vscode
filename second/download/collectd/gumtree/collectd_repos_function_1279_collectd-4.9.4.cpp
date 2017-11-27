static void submit_counter2 (const char *dev, const char *type, const char *ti1,
				const char *ti2, counter_t val1, counter_t val2)
{
	value_t items[2];
	items[0].counter = val1;
	items[1].counter = val2;
	submit (dev, type, ti1, ti2, items, 2);
}