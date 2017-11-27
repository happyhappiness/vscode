static void submit_counter (const char *dev, const char *type, const char *ti1,
				const char *ti2, counter_t val)
{
	value_t item;
	item.counter = val;
	submit (dev, type, ti1, ti2, &item, 1);
}